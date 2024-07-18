# mbedtls&wireshark软件

## 1. mbedtls

**system**: 

```
今天的主题是mbedtls&wireshark软件。
```

**user**: 

```
请帮我看下mbedtls的代码。
文件：mbedtls/library/ssl_tls.c
函数：/*
 * Once the certificate message is read, parse it into a cert chain and
 * perform basic checks, but leave actual verification to the caller
 */
MBEDTLS_CHECK_RETURN_CRITICAL
static int ssl_parse_certificate_chain(mbedtls_ssl_context *ssl,
                                       mbedtls_x509_crt *chain)
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
#if defined(MBEDTLS_SSL_RENEGOTIATION) && defined(MBEDTLS_SSL_CLI_C)
    int crt_cnt = 0;
#endif
    size_t i, n;
    uint8_t alert;

    if (ssl->in_msgtype != MBEDTLS_SSL_MSG_HANDSHAKE) {
        MBEDTLS_SSL_DEBUG_MSG(1, ("bad certificate message"));
        mbedtls_ssl_send_alert_message(ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                       MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE);
        return MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE;
    }

    if (ssl->in_msg[0] != MBEDTLS_SSL_HS_CERTIFICATE) {
        mbedtls_ssl_send_alert_message(ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                       MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE);
        return MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE;
    }

    if (ssl->in_hslen < mbedtls_ssl_hs_hdr_len(ssl) + 3 + 3) {
        MBEDTLS_SSL_DEBUG_MSG(1, ("bad certificate message"));
        mbedtls_ssl_send_alert_message(ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                       MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR);
        return MBEDTLS_ERR_SSL_DECODE_ERROR;
    }

    i = mbedtls_ssl_hs_hdr_len(ssl);

    /*
     * Same message structure as in mbedtls_ssl_write_certificate()
     */
    n = MBEDTLS_GET_UINT16_BE(ssl->in_msg, i + 1);

    if (ssl->in_msg[i] != 0 ||
        ssl->in_hslen != n + 3 + mbedtls_ssl_hs_hdr_len(ssl)) {
        MBEDTLS_SSL_DEBUG_MSG(1, ("bad certificate message"));
        mbedtls_ssl_send_alert_message(ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                       MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR);
        return MBEDTLS_ERR_SSL_DECODE_ERROR;
    }

    /* Make &ssl->in_msg[i] point to the beginning of the CRT chain. */
    i += 3;

    /* Iterate through and parse the CRTs in the provided chain. */
    while (i < ssl->in_hslen) {
        /* Check that there's room for the next CRT's length fields. */
        if (i + 3 > ssl->in_hslen) {
            MBEDTLS_SSL_DEBUG_MSG(1, ("bad certificate message"));
            mbedtls_ssl_send_alert_message(ssl,
                                           MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                           MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR);
            return MBEDTLS_ERR_SSL_DECODE_ERROR;
        }
        /* In theory, the CRT can be up to 2**24 Bytes, but we don't support
         * anything beyond 2**16 ~ 64K. */
        if (ssl->in_msg[i] != 0) {
            MBEDTLS_SSL_DEBUG_MSG(1, ("bad certificate message"));
            mbedtls_ssl_send_alert_message(ssl,
                                           MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                           MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT);
            return MBEDTLS_ERR_SSL_BAD_CERTIFICATE;
        }

        /* Read length of the next CRT in the chain. */
        n = MBEDTLS_GET_UINT16_BE(ssl->in_msg, i + 1);
        i += 3;

        if (n < 128 || i + n > ssl->in_hslen) {
            MBEDTLS_SSL_DEBUG_MSG(1, ("bad certificate message"));
            mbedtls_ssl_send_alert_message(ssl,
                                           MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                           MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR);
            return MBEDTLS_ERR_SSL_DECODE_ERROR;
        }

        /* Check if we're handling the first CRT in the chain. */
#if defined(MBEDTLS_SSL_RENEGOTIATION) && defined(MBEDTLS_SSL_CLI_C)
        if (crt_cnt++ == 0 &&
            ssl->conf->endpoint == MBEDTLS_SSL_IS_CLIENT &&
            ssl->renego_status == MBEDTLS_SSL_RENEGOTIATION_IN_PROGRESS) {
            /* During client-side renegotiation, check that the server's
             * end-CRTs hasn't changed compared to the initial handshake,
             * mitigating the triple handshake attack. On success, reuse
             * the original end-CRT instead of parsing it again. */
            MBEDTLS_SSL_DEBUG_MSG(3, ("Check that peer CRT hasn't changed during renegotiation"));
            if (ssl_check_peer_crt_unchanged(ssl,
                                             &ssl->in_msg[i],
                                             n) != 0) {
                MBEDTLS_SSL_DEBUG_MSG(1, ("new server cert during renegotiation"));
                mbedtls_ssl_send_alert_message(ssl,
                                               MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                               MBEDTLS_SSL_ALERT_MSG_ACCESS_DENIED);
                return MBEDTLS_ERR_SSL_BAD_CERTIFICATE;
            }

            /* Now we can safely free the original chain. */
            ssl_clear_peer_cert(ssl->session);
        }
#endif /* MBEDTLS_SSL_RENEGOTIATION && MBEDTLS_SSL_CLI_C */

        /* Parse the next certificate in the chain. */
#if defined(MBEDTLS_SSL_KEEP_PEER_CERTIFICATE)
        ret = mbedtls_x509_crt_parse_der(chain, ssl->in_msg + i, n);
#else
        /* If we don't need to store the CRT chain permanently, parse
         * it in-place from the input buffer instead of making a copy. */
        ret = mbedtls_x509_crt_parse_der_nocopy(chain, ssl->in_msg + i, n);
#endif /* MBEDTLS_SSL_KEEP_PEER_CERTIFICATE */
        switch (ret) {
            case 0: /*ok*/
            case MBEDTLS_ERR_X509_UNKNOWN_SIG_ALG + MBEDTLS_ERR_OID_NOT_FOUND:
                /* Ignore certificate with an unknown algorithm: maybe a
                   prior certificate was already trusted. */
                break;

            case MBEDTLS_ERR_X509_ALLOC_FAILED:
                alert = MBEDTLS_SSL_ALERT_MSG_INTERNAL_ERROR;
                goto crt_parse_der_failed;

            case MBEDTLS_ERR_X509_UNKNOWN_VERSION:
                alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
                goto crt_parse_der_failed;

            default:
                alert = MBEDTLS_SSL_ALERT_MSG_BAD_CERT;
crt_parse_der_failed:
                mbedtls_ssl_send_alert_message(ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL, alert);
                MBEDTLS_SSL_DEBUG_RET(1, " mbedtls_x509_crt_parse_der", ret);
                return ret;
        }

        i += n;
    }

    MBEDTLS_SSL_DEBUG_CRT(3, "peer certificate", chain);
    return 0;
}
1.解释参数、返回值和大致流程
2.重点关注返回MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE的场景。
```

**assistant**: 

```
好的，我来详细解释一下 `ssl_parse_certificate_chain` 函数的参数、返回值和大致流程，并重点关注返回 `MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE` 的场景。

### 参数

- `mbedtls_ssl_context *ssl`: 这是一个指向 SSL 上下文的指针，包含了 SSL 会话的所有相关信息。
- `mbedtls_x509_crt *chain`: 这是一个指向 X.509 证书链的指针，用于存储解析后的证书链。

### 返回值

该函数返回一个整数，表示操作的结果。可能的返回值包括：
- `0`: 表示成功解析证书链。
- `MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE`: 表示收到的消息类型或消息内容不符合预期。
- `MBEDTLS_ERR_SSL_DECODE_ERROR`: 表示消息解码失败。
- `MBEDTLS_ERR_SSL_BAD_CERTIFICATE`: 表示证书解析失败。
- 其他错误码: 可能来自证书解析函数 `mbedtls_x509_crt_parse_der` 或 `mbedtls_x509_crt_parse_der_nocopy`。

### 大致流程

1. **检查消息类型**:
   - 如果 `ssl->in_msgtype` 不是 `MBEDTLS_SSL_MSG_HANDSHAKE`，则返回 `MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE`。
   - 如果 `ssl->in_msg[0]` 不是 `MBEDTLS_SSL_HS_CERTIFICATE`，则返回 `MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE`。

2. **检查消息长度**:
   - 如果消息长度不符合预期（小于握手头长度加上最小的证书消息长度），则返回 `MBEDTLS_ERR_SSL_DECODE_ERROR`。

3. **解析证书链**:
   - 逐个解析证书链中的每个证书，检查每个证书的长度和内容。
   - 如果证书解析失败，根据不同的错误返回不同的错误码。

### 返回 `MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE` 的场景

函数中有两个地方可能返回 `MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE`：

1. **消息类型检查**:
   
   if (ssl->in_msgtype != MBEDTLS_SSL_MSG_HANDSHAKE) {
       MBEDTLS_SSL_DEBUG_MSG(1, ("bad certificate message"));
       mbedtls_ssl_send_alert_message(ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                      MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE);
       return MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE;
   }
   
   如果接收到的消息类型不是握手消息 (`MBEDTLS_SSL_MSG_HANDSHAKE`)，则函数认为这是一个意外消息，发送一个致命警报并返回 `MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE`。

2. **消息内容检查**:
   
   if (ssl->in_msg[0] != MBEDTLS_SSL_HS_CERTIFICATE) {
       mbedtls_ssl_send_alert_message(ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                      MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE);
       return MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE;
   }
   
   如果接收到的消息内容的第一个字节不是证书消息 (`MBEDTLS_SSL_HS_CERTIFICATE`)，则函数认为这是一个意外消息，发送一个致命警报并返回 `MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE`。

### 总结

`ssl_parse_certificate_chain` 函数的主要作用是解析接收到的证书链并进行基本的检查。函数首先检查消息类型和内容是否符合预期，如果不符合则返回 `MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE`。如果消息类型和内容正确，则继续解析证书链中的每个证书，检查证书的长度和内容，并处理可能的解析错误。
```

**user**: 

```
如果使用wireshark抓包，我该如何找到ssl的内容（即mbedtls_ssl_context *ssl）？
```

**assistant**: 

```
使用Wireshark抓包来分析SSL/TLS通信，可以帮助你查看传输的数据包内容，但无法直接找到或查看 `mbedtls_ssl_context *ssl` 的具体内容。`mbedtls_ssl_context` 是在应用程序内存中维护的结构，Wireshark只能捕获网络传输的数据包，而无法直接访问应用程序内存。

不过，你可以通过Wireshark抓包来分析SSL/TLS通信的内容，了解SSL/TLS握手过程、证书交换、加密算法协商等信息。以下是一些步骤和提示，帮助你使用Wireshark分析SSL/TLS通信：

### 步骤

1. **启动Wireshark并开始捕获**:
   - 打开Wireshark，选择合适的网络接口。
   - 点击“开始捕获”按钮。

2. **捕获SSL/TLS流量**:
   - 运行你的应用程序，确保它正在进行SSL/TLS通信。
   - Wireshark会捕获所有经过该网络接口的流量，包括SSL/TLS数据包。

3. **使用过滤器筛选SSL/TLS流量**:
   - 在Wireshark的过滤器栏中输入 `ssl` 或 `tls`，然后按回车键。这样可以只显示SSL/TLS相关的数据包。
   - 你也可以使用更具体的过滤器，例如 `tcp.port == 443`，如果你知道SSL/TLS通信使用的端口。

4. **分析SSL/TLS握手**:
   - 找到SSL/TLS握手过程的数据包。这些数据包通常包括 `Client Hello`、`Server Hello`、`Certificate`、`Server Key Exchange`、`Client Key Exchange` 等。
   - 右键点击一个数据包，选择“Follow” -> “TCP Stream”或“SSL Stream”，可以查看整个SSL/TLS会话。

5. **解密SSL/TLS流量（可选）**:
   - 如果你有服务器的私钥，或者你在客户端配置了密钥日志文件，可以在Wireshark中配置这些信息来解密SSL/TLS流量。
   - 在Wireshark中，选择“Edit” -> “Preferences” -> “Protocols” -> “TLS”，然后在“(Pre)-Master-Secret log filename”字段中指定密钥日志文件路径。
   - 使用 `SSLKEYLOGFILE` 环境变量可以生成密钥日志文件。例如，在Linux或macOS终端中运行：
     
     export SSLKEYLOGFILE=~/sslkeys.log
     
     然后运行你的应用程序，密钥日志文件会记录会话密钥。

### 提示

- **查看证书信息**:
  - 在Wireshark中找到 `Certificate` 消息，展开详细信息，可以查看传输的证书内容。

- **检查握手失败原因**:
  - 如果SSL/TLS握手失败，查看握手消息和警报消息，可以帮助你诊断问题。

- **了解协议细节**:
  - Wireshark可以详细解析SSL/TLS协议的各个字段，帮助你理解协议的工作原理。

### 总结

虽然Wireshark无法直接显示 `mbedtls_ssl_context *ssl` 的内容，但它可以帮助你捕获和分析SSL/TLS通信的具体数据包，了解握手过程和传输的数据。通过解密流量，你可以查看加密前的应用数据，这对于调试和分析SSL/TLS通信非常有用。
```

**user**: 

```
换言之，mbedtls_ssl_context *ssl 的内容，在数据包中是如何体现的？毕竟这个是先通过网络中传输到应用程序，然后才能在内存中解析的吧？
```

**assistant**: 

```
理解 `mbedtls_ssl_context *ssl` 在数据包中的体现，需要先了解SSL/TLS通信的工作原理。SSL/TLS协议在网络传输中涉及多个阶段，包括握手阶段和数据传输阶段。`mbedtls_ssl_context` 结构体在这些过程中存储了大量的状态信息和会话数据。

### SSL/TLS 通信阶段

1. **握手阶段**:
   - 客户端和服务器交换握手消息，协商协议版本、加密算法、会话密钥等。
   - 典型的握手消息包括 `ClientHello`、`ServerHello`、`Certificate`、`ServerKeyExchange`、`ClientKeyExchange`、`Finished` 等。

2. **数据传输阶段**:
   - 握手完成后，客户端和服务器使用协商好的会话密钥进行加密通信。
   - 数据包的内容被加密，只有持有正确会话密钥的通信双方才能解密。

### mbedtls_ssl_context 在数据包中的体现

`mbedtls_ssl_context` 结构体在内存中存储了SSL/TLS会话的状态信息，但在网络传输中，这些信息被封装在SSL/TLS协议的数据包中。以下是一些关键点：

1. **握手消息**:
   - `mbedtls_ssl_context` 中的许多字段是从握手消息中提取并存储的。例如，客户端和服务器的随机数（`ClientHello` 和 `ServerHello` 中的 `random` 字段）、会话ID、加密算法、证书等。
   - Wireshark可以捕获和解析这些握手消息，显示详细的字段内容。

2. **加密数据**:
   - 握手完成后，应用数据通过SSL/TLS层进行加密，然后再通过网络传输。
   - `mbedtls_ssl_context` 中存储了加密所需的密钥和状态信息。
   - 在Wireshark中，数据包的负载部分会显示为加密数据。如果你有会话密钥，可以在Wireshark中解密这些数据。

### 示例：握手消息

假设你在Wireshark中捕获到一个SSL/TLS握手数据包，例如 `ClientHello`。这个数据包可能包含以下信息：

- 客户端随机数（`random`）
- 支持的加密套件（`cipher_suites`）
- 支持的压缩方法（`compression_methods`）
- 扩展字段（`extensions`）

这些信息在传输到服务器后，会被解析并存储在 `mbedtls_ssl_context` 结构体中。例如：

- `ssl->handshake->randbytes` 存储客户端和服务器的随机数。
- `ssl->session_negotiate->cipher_suite` 存储协商好的加密套件。
- `ssl->session_negotiate->compression` 存储协商好的压缩方法。

### 示例：应用数据

在数据传输阶段，应用数据被加密并通过网络传输。假设你在Wireshark中捕获到一个加密的数据包：

- 数据包的负载部分是加密的应用数据。
- `mbedtls_ssl_context` 中的密钥和状态信息用于加密和解密这些数据。

如果你有会话密钥，可以在Wireshark中配置密钥文件来解密这些数据包，查看原始的应用数据。

### 总结

`mbedtls_ssl_context` 结构体在内存中存储了SSL/TLS会话的各种状态信息和密钥，这些信息是从握手消息和数据传输过程中提取和生成的。在网络传输中，这些信息被封装在SSL/TLS协议的数据包中，并以加密形式传输。Wireshark可以帮助你捕获和解析这些数据包，了解握手过程和传输的数据，但无法直接查看 `mbedtls_ssl_context` 结构体的内容。通过解密SSL/TLS流量，你可以查看加密前的应用数据，这对于调试和分析SSL/TLS通信非常有用。
```

**user**: 

```
一些基本信息：
36	4.031800	10.203.113.50	10.18.23.106	TLSv1.2	116	Server Hello, Certificate, Server Key Exchange, Certificate Request, Server Hello Done
37	4.036984	10.18.23.106	10.203.113.50	TCP	54	51505 → 31240 [ACK] Seq=93 Ack=4351 Win=902 Len=0
38	4.037868	10.18.23.106	10.203.113.50	TCP	54	[TCP Window Update] 51505 → 31240 [ACK] Seq=93 Ack=4351 Win=1500 Len=0
39	4.189139	10.18.23.106	10.203.113.50	TLSv1.2	61	Alert (Level: Fatal, Description: Certificate Unknown)
40	4.189555	10.203.113.50	10.18.23.106	TCP	54	31240 → 51505 [FIN, ACK] Seq=4351 Ack=100 Win=29440 Len=0

```

**assistant**: 

```
从你提供的基本信息来看，这是一段SSL/TLS握手的Wireshark抓包记录。我们可以看到握手过程中的一些关键步骤以及最终的握手失败情况。以下是对这些数据包的详细解释：

### 数据包详细解释

#### 数据包 36: Server Hello, Certificate, Server Key Exchange, Certificate Request, Server Hello Done
- **源IP地址**: 10.203.113.50
- **目的IP地址**: 10.18.23.106
- **协议**: TLSv1.2
- **长度**: 116 字节
- **内容**:
  - `Server Hello`: 服务器响应客户端的 `Client Hello`，并提供服务器的随机数、会话ID、加密套件等信息。
  - `Certificate`: 服务器发送其证书链。
  - `Server Key Exchange`: 服务器发送公钥交换信息（例如，Diffie-Hellman参数）。
  - `Certificate Request`: 服务器请求客户端提供其证书（双向认证）。
  - `Server Hello Done`: 服务器握手消息结束，等待客户端响应。

#### 数据包 37: TCP ACK
- **源IP地址**: 10.18.23.106
- **目的IP地址**: 10.203.113.50
- **协议**: TCP
- **长度**: 54 字节
- **内容**: 
  - 这是一个TCP ACK数据包，确认接收到的数据包36。

#### 数据包 38: TCP Window Update
- **源IP地址**: 10.18.23.106
- **目的IP地址**: 10.203.113.50
- **协议**: TCP
- **长度**: 54 字节
- **内容**: 
  - 这是一个TCP窗口更新数据包，调整接收窗口大小。

#### 数据包 39: Alert (Level: Fatal, Description: Certificate Unknown)
- **源IP地址**: 10.18.23.106
- **目的IP地址**: 10.203.113.50
- **协议**: TLSv1.2
- **长度**: 61 字节
- **内容**: 
  - 这是一个TLS警报消息，表示客户端无法识别服务器的证书。
  - 警报等级为致命（Fatal），描述为证书未知（Certificate Unknown）。

#### 数据包 40: TCP FIN, ACK
- **源IP地址**: 10.203.113.50
- **目的IP地址**: 10.18.23.106
- **协议**: TCP
- **长度**: 54 字节
- **内容**: 
  - 这是一个TCP FIN数据包，表示服务器关闭连接。

### 分析与解释

从这些数据包中可以看出，SSL/TLS握手在服务器发送 `Server Hello` 和相关消息后，客户端无法识别服务器的证书并发送了一个致命警报消息（Certificate Unknown）。这导致握手失败，服务器随后关闭连接。

### mbedtls_ssl_context 在这些数据包中的体现

虽然Wireshark无法直接显示 `mbedtls_ssl_context` 的内容，但我们可以推测 `mbedtls_ssl_context` 在这些数据包中的一些状态和操作：

1. **Server Hello, Certificate, Server Key Exchange, Certificate Request, Server Hello Done**:
   - 服务器在发送这些消息时，`mbedtls_ssl_context` 中存储了握手的状态信息，包括服务器的随机数、会话ID、加密套件、证书链等。
   - 这些信息在网络数据包中具体表现为 `Server Hello`、`Certificate`、`Server Key Exchange` 等消息。

2. **Alert (Level: Fatal, Description: Certificate Unknown)**:
   - 客户端在接收到服务器的证书后，使用 `mbedtls_ssl_context` 中的函数解析和验证证书。
   - 由于证书验证失败，客户端生成一个致命警报消息，并通过网络发送。
   - `mbedtls_ssl_context` 中会记录警报的详细信息和握手状态。

### 总结

通过Wireshark抓包，我们可以看到SSL/TLS握手过程中的具体消息和状态变化。虽然我们无法直接查看 `mbedtls_ssl_context` 的内容，但这些数据包反映了 `mbedtls_ssl_context` 在握手过程中的状态和操作。例如，握手消息（如 `Server Hello`、`Certificate`）反映了 `mbedtls_ssl_context` 中存储的握手状态信息，而警报消息（如 `Certificate Unknown`）反映了证书验证失败的结果。通过分析这些数据包，我们可以更好地理解SSL/TLS握手过程和 `mbedtls_ssl_context` 的作用。
```

**user**: 

```
请你总结我们的对话。
```

**assistant**: 

```
当然，以下是我们对话的总结：

1. **mbedTLS 代码分析**:
   - 我们讨论了 `ssl_parse_certificate_chain` 函数的作用和流程。这个函数用于解析证书链，执行基本的校验，并留给调用者进行进一步的验证。
   - 函数的参数包括 `mbedtls_ssl_context *ssl`（SSL上下文）和 `mbedtls_x509_crt *chain`（证书链）。
   - 返回值主要是错误码，包括成功（0）或各种错误情况，如 `MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE` 表示接收到了意外的消息类型或内容。
   - 函数流程包括消息类型检查、长度检查、证书链的解析和错误处理。

2. **Wireshark 抓包分析**:
   - 我们讨论了如何使用Wireshark来捕获和分析SSL/TLS通信数据。虽然Wireshark不能直接显示 `mbedtls_ssl_context` 结构体的内容，但它可以捕获网络传输的数据包。
   - 可以通过设置过滤器来查看SSL/TLS相关的数据包，并可以进一步分析握手过程和加密数据。
   - 如果有访问权限，可以配置Wireshark来解密SSL/TLS流量，以查看加密前的应用数据。

3. **SSL/TLS 握手过程**:
   - 我们分析了一系列Wireshark抓包记录，这些记录显示了SSL/TLS握手的一些关键步骤，包括服务器的 `Server Hello`、`Certificate`、`Server Key Exchange`、`Certificate Request` 和 `Server Hello Done`。
   - 记录显示了客户端因无法识别服务器证书而发送的致命警报（`Certificate Unknown`），导致服务器关闭了连接。

4. **mbedtls_ssl_context 在网络传输中的体现**:
   - 我们讨论了 `mbedtls_ssl_context` 结构体在网络传输中的体现，以及它在握手阶段和数据传输阶段存储的状态信息和会话数据是如何在数据包中封装和传输的。
   - 虽然不能直接查看 `mbedtls_ssl_context` 的内容，但通过分析Wireshark抓包记录可以推断出 `mbedtls_ssl_context` 在SSL/TLS通信过程中的作用和状态。

整个对话旨在帮助你理解mbedTLS代码在SSL/TLS通信中的应用，以及如何使用Wireshark来分析SSL/TLS通信的数据包。
```

**user**: 

```
现在，让我们聚焦两个核心错误码：
Certificate Unknown (46)，对应mbedtls中的ssl.h文件中的#define MBEDTLS_SSL_ALERT_MSG_CERT_UNKNOWN          46  /* 0x2E */
MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE (0x7700)，对应mbedtls中的ssl.h文件中的/** An unexpected message was received from our peer. */
#define MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE                -0x7700
由这两个错误码，我们大致可以定位到ssl_parse_certificate_chain最初的部分报错（对吗？），即：
static int ssl_parse_certificate_chain(mbedtls_ssl_context *ssl,
mbedtls_x509_crt *chain)
{
int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
#if defined(MBEDTLS_SSL_RENEGOTIATION) && defined(MBEDTLS_SSL_CLI_C)
int crt_cnt = 0;
#endif
size_t i, n;
uint8_t alert;

if (ssl->in_msgtype != MBEDTLS_SSL_MSG_HANDSHAKE) {
MBEDTLS_SSL_DEBUG_MSG(1, ("bad certificate message"));
mbedtls_ssl_send_alert_message(ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE);
return MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE;
}

if (ssl->in_msg[0] != MBEDTLS_SSL_HS_CERTIFICATE) {
mbedtls_ssl_send_alert_message(ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE);
return MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE;
}
如果要启用mbedtls调试，我们应该如何添加调试打印？

```

**assistant**: 

```
在mbedTLS中，错误码 `MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE` 和警报消息 `MBEDTLS_SSL_ALERT_MSG_CERT_UNKNOWN` 通常指示不同的错误条件。

### MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE
这个错误码通常表示在SSL/TLS握手过程中收到了一个意外的消息。在 `ssl_parse_certificate_chain` 函数中，它会在以下两种情况下返回：

1. 如果接收到的消息类型 `ssl->in_msgtype` 不是握手消息 (`MBEDTLS_SSL_MSG_HANDSHAKE`)。
2. 如果握手消息的第一个字节 `ssl->in_msg[0]` 不是证书消息 (`MBEDTLS_SSL_HS_CERTIFICATE`)。

### MBEDTLS_SSL_ALERT_MSG_CERT_UNKNOWN
这是一个警报消息，它指示证书无法被识别或者证书链验证失败。在Wireshark的抓包记录中，当客户端发送一个警报消息 `Alert (Level: Fatal, Description: Certificate Unknown)` 时，这个警报对应的就是 `MBEDTLS_SSL_ALERT_MSG_CERT_UNKNOWN`。

### 启用mbedTLS调试

要在mbedTLS中启用调试输出，你需要做以下几步：

1. **配置mbedTLS**:
   - 确保在编译mbedTLS时启用了调试功能。在mbedTLS的配置文件 `config.h` 中，你需要启用 `MBEDTLS_DEBUG_C`。

2. **设置调试等级**:
   - 调用 `mbedtls_ssl_conf_dbg` 函数来设置调试回调函数和调试阈值。调试阈值是一个介于0到4的数字，它定义了输出的详细程度。等级4是最详细的。

3. **实现调试回调函数**:
   - 实现一个调试回调函数，这个函数将被mbedTLS用来输出调试信息。通常，这个函数会将调试信息输出到标准输出或者日志文件。


void my_debug(void *ctx, int level, const char *file, int line, const char *str)
{
    if (level <= ((int *) ctx))
    {
        fprintf((FILE *) stderr, "%s:%04d: %s", file, line, str);
        fflush((FILE *) stderr);
    }
}


4. **配置SSL上下文**:
   - 在设置SSL上下文时，调用上面定义的 `my_debug` 函数。


mbedtls_ssl_conf_dbg(&ssl_conf, my_debug, stdout);
mbedtls_ssl_conf_log_level(&ssl_conf, MBEDTLS_DEBUG_LEVEL);


其中 `MBEDTLS_DEBUG_LEVEL` 是你希望的调试等级。

### 总结
你正确地指出，根据Wireshark抓包记录中的警报消息 `Certificate Unknown`，我们可以推断可能在 `ssl_parse_certificate_chain` 函数的最初部分报错。然而，这个警报消息更可能是在证书验证过程中产生的，而不是在消息类型检查时。如果要确切地定位问题，启用mbedTLS的调试功能并设置适当的调试等级将非常有帮助，这样你可以获得关于错误发生时上下文的详细信息。
```

**user**: 

```
你说得有道理。事实上，我的一个比较迷惑的点就是：在int mbedtls_ssl_parse_certificate(mbedtls_ssl_context *ssl)这个函数中有这么一段：
    ret = ssl_parse_certificate_chain(ssl, chain);
    if (ret != 0) {
        goto exit;
    }
    ret = ssl_parse_certificate_verify(ssl, authmode,
                                       chain, rs_ctx);
    if (ret != 0) {
        goto exit;
    }
其中，上面的函数你已经看过了，下面的函数包含这些内容（截取）：
    if (ret != 0) {
        uint8_t alert;

        /* The certificate may have been rejected for several reasons.
           Pick one and send the corresponding alert. Which alert to send
           may be a subject of debate in some cases. */
        if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_OTHER) {
            alert = MBEDTLS_SSL_ALERT_MSG_ACCESS_DENIED;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_CN_MISMATCH) {
            alert = MBEDTLS_SSL_ALERT_MSG_BAD_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_KEY_USAGE) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_EXT_KEY_USAGE) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_NS_CERT_TYPE) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_BAD_PK) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_BAD_KEY) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_EXPIRED) {
            alert = MBEDTLS_SSL_ALERT_MSG_CERT_EXPIRED;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_REVOKED) {
            alert = MBEDTLS_SSL_ALERT_MSG_CERT_REVOKED;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_NOT_TRUSTED) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNKNOWN_CA;
        } else {
            alert = MBEDTLS_SSL_ALERT_MSG_CERT_UNKNOWN;
        }
        mbedtls_ssl_send_alert_message(ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                       alert);
    }
可以观察到，二者都调用了mbedtls_ssl_send_alert_message这个函数，而实际上，抓到的报文内容是Certificate Unknown (46)，至于0x7700的错误是怎么报出来的，我可能还要查阅一下上层的日志代码。你怎么看？
```

**assistant**: 

```
你提出的疑惑很有道理。我们可以通过详细分析 `mbedtls_ssl_parse_certificate` 和相关函数的执行流程，来理解错误码和警报消息的产生过程。

### 分析 `mbedtls_ssl_parse_certificate` 函数

在 `mbedtls_ssl_parse_certificate` 函数中，主要的步骤包括：

1. 调用 `ssl_parse_certificate_chain` 函数解析证书链。
2. 如果解析失败，返回错误。
3. 调用 `ssl_parse_certificate_verify` 函数验证证书。
4. 如果验证失败，发送相应的警报消息并返回错误。

### 具体代码分析

#### `ssl_parse_certificate_chain` 函数


int ssl_parse_certificate_chain(mbedtls_ssl_context *ssl, mbedtls_x509_crt *chain)
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    size_t i, n;
    uint8_t alert;

    if (ssl->in_msgtype != MBEDTLS_SSL_MSG_HANDSHAKE) {
        MBEDTLS_SSL_DEBUG_MSG(1, ("bad certificate message"));
        mbedtls_ssl_send_alert_message(ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                       MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE);
        return MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE;
    }

    if (ssl->in_msg[0] != MBEDTLS_SSL_HS_CERTIFICATE) {
        mbedtls_ssl_send_alert_message(ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                       MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE);
        return MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE;
    }

    // 其他解析证书链的代码...

    return 0;
}


#### `ssl_parse_certificate_verify` 函数


int ssl_parse_certificate_verify(mbedtls_ssl_context *ssl, int authmode,
                                 mbedtls_x509_crt *chain, void *rs_ctx)
{
    int ret = mbedtls_x509_crt_verify(chain, ssl->session_negotiate->ca_chain,
                                      ssl->session_negotiate->ca_crl,
                                      ssl->session_negotiate->peer_cert,
                                      &ssl->session_negotiate->verify_result,
                                      ssl->conf->f_vrfy, ssl->conf->p_vrfy);

    if (ret != 0) {
        uint8_t alert;

        // 根据不同的证书验证错误，发送相应的警报消息
        if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_OTHER) {
            alert = MBEDTLS_SSL_ALERT_MSG_ACCESS_DENIED;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_CN_MISMATCH) {
            alert = MBEDTLS_SSL_ALERT_MSG_BAD_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_KEY_USAGE) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_EXT_KEY_USAGE) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_NS_CERT_TYPE) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_BAD_PK) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_BAD_KEY) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_EXPIRED) {
            alert = MBEDTLS_SSL_ALERT_MSG_CERT_EXPIRED;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_REVOKED) {
            alert = MBEDTLS_SSL_ALERT_MSG_CERT_REVOKED;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_NOT_TRUSTED) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNKNOWN_CA;
        } else {
            alert = MBEDTLS_SSL_ALERT_MSG_CERT_UNKNOWN;
        }
        mbedtls_ssl_send_alert_message(ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL, alert);
    }

    return ret;
}


### 错误码和警报消息的产生过程

1. **`MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE` 错误码**:
   - 在 `ssl_parse_certificate_chain` 函数中，如果接收到的消息类型不是握手消息 (`MBEDTLS_SSL_MSG_HANDSHAKE`) 或者握手消息的第一个字节不是证书消息 (`MBEDTLS_SSL_HS_CERTIFICATE`)，将发送一个 `MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE` 警报，并返回 `MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE` 错误码。

2. **`MBEDTLS_SSL_ALERT_MSG_CERT_UNKNOWN` 警报消息**:
   - 在 `ssl_parse_certificate_verify` 函数中，如果证书验证失败，根据 `verify_result` 的不同，将发送不同的警报消息。如果没有匹配的具体错误类型，将发送 `MBEDTLS_SSL_ALERT_MSG_CERT_UNKNOWN` 警报。

### 启用mbedTLS调试

要启用mbedTLS调试功能并添加调试打印，可以按照以下步骤进行：

1. **在 `config.h` 中启用调试**:
   - 确保在 `config.h` 文件中启用了调试功能：
     
     #define MBEDTLS_DEBUG_C
     

2. **实现调试回调函数**:
   - 实现一个调试回调函数，例如：
     
     void my_debug(void *ctx, int level, const char *file, int line, const char *str)
     {
         fprintf((FILE *) ctx, "%s:%04d: %s", file, line, str);
         fflush((FILE *) ctx);
     }
     

3. **配置SSL上下文**:
   - 在设置SSL上下文时，调用调试回调函数，并设置调试级别：
     
     mbedtls_ssl_conf_dbg(&ssl_conf, my_debug, stderr);
     mbedtls_debug_set_threshold(4); // 设置调试级别为4（最详细）
     

通过启用调试功能，你可以获得详细的调试信息，帮助你更好地理解错误发生的上下文。

### 总结

你观察到的 `Certificate Unknown (46)` 警报消息是在证书验证过程中产生的，而 `MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE (0x7700)` 错误码则是在消息类型检查时产生的。这两个错误码和警报消息分别对应于不同的错误条件。通过启用mbedTLS的调试功能，你可以获得更多的调试信息，帮助你更好地定位和解决问题。
```

**user**: 

```
请详细解释你的my_debug回调函数。
```

**assistant**: 

```
当然，下面是对 `my_debug` 回调函数的详细解释。

### `my_debug` 回调函数

`my_debug` 回调函数是一个调试回调函数，用于处理和输出mbedTLS生成的调试信息。mbedTLS库在运行过程中会调用这个函数来输出调试信息。你可以自定义这个函数，以便将调试信息输出到你希望的位置（例如标准输出、日志文件等）。

#### 函数定义


void my_debug(void *ctx, int level, const char *file, int line, const char *str)
{
    fprintf((FILE *) ctx, "%s:%04d: %s", file, line, str);
    fflush((FILE *) ctx);
}


#### 参数解释

- `void *ctx`: 上下文指针，通常用于传递文件指针或其他输出目标。在配置调试回调函数时，你可以指定这个参数。例如，你可以将 `stderr` 或者一个文件指针传递给这个参数。
- `int level`: 调试级别。mbedTLS会根据设置的调试级别调用这个回调函数。调试级别从0到4，0表示最少的调试信息，4表示最详细的调试信息。
- `const char *file`: 源文件名。mbedTLS库输出调试信息时会包含源文件名，以便你知道调试信息来自哪个源文件。
- `int line`: 源文件中的行号。mbedTLS库输出调试信息时会包含行号，以便你知道调试信息来自源文件的哪一行。
- `const char *str`: 调试信息字符串。mbedTLS库生成的调试信息字符串。

#### 函数实现


void my_debug(void *ctx, int level, const char *file, int line, const char *str)
{
    fprintf((FILE *) ctx, "%s:%04d: %s", file, line, str);
    fflush((FILE *) ctx);
}


- `fprintf((FILE *) ctx, "%s:%04d: %s", file, line, str);`
  - 使用 `fprintf` 函数将调试信息输出到 `ctx` 指定的文件指针。`ctx` 通常是一个 `FILE *` 类型的指针，例如 `stderr` 或者一个打开的文件指针。
  - 输出格式为：`文件名:行号: 调试信息`。例如：`ssl_tls.c:1234: handshake message received`。

- `fflush((FILE *) ctx);`
  - 使用 `fflush` 函数强制刷新输出缓冲区，确保调试信息立即被写入到指定的输出目标。这对于调试信息的实时性非常重要，尤其是在调试过程中，你希望立即看到输出的调试信息。

### 配置调试回调函数

在配置mbedTLS的SSL上下文时，你需要设置调试回调函数，并指定调试级别。以下是一个示例：


mbedtls_ssl_context ssl;
mbedtls_ssl_config conf;

// 初始化SSL上下文和配置
mbedtls_ssl_init(&ssl);
mbedtls_ssl_config_init(&conf);

// 配置SSL上下文
mbedtls_ssl_setup(&ssl, &conf);

// 设置调试回调函数
mbedtls_ssl_conf_dbg(&conf, my_debug, stderr);

// 设置调试级别
mbedtls_debug_set_threshold(4); // 调试级别为4，最详细


- `mbedtls_ssl_conf_dbg(&conf, my_debug, stderr);`
  - 设置调试回调函数为 `my_debug`，并将 `stderr` 作为上下文指针传递给回调函数。这意味着调试信息将输出到标准错误输出。

- `mbedtls_debug_set_threshold(4);`
  - 设置调试级别为4，表示输出最详细的调试信息。

### 总结

`my_debug` 回调函数是一个简单而有效的调试工具，用于处理和输出mbedTLS库生成的调试信息。通过配置调试回调函数和设置调试级别，你可以获得详细的调试信息，帮助你理解和解决mbedTLS库在运行过程中遇到的问题。
```

**user**: 

```
请试着展示如何调试 ssl_parse_certificate_chain 函数和 ssl_parse_certificate_verify 函数。
```

**assistant**: 

```
好的，下面我将展示如何使用 `my_debug` 回调函数调试 `ssl_parse_certificate_chain` 和 `ssl_parse_certificate_verify` 函数。我们将通过添加调试信息来跟踪函数的执行流程和错误处理。

### 设置调试环境

首先，确保你已经启用了mbedTLS的调试功能，并配置了调试回调函数。以下是配置调试回调函数的代码示例：


#include "mbedtls/debug.h"
#include "mbedtls/ssl.h"
#include "mbedtls/x509_crt.h"

void my_debug(void *ctx, int level, const char *file, int line, const char *str)
{
    fprintf((FILE *) ctx, "%s:%04d: %s", file, line, str);
    fflush((FILE *) ctx);
}

int main(void)
{
    mbedtls_ssl_context ssl;
    mbedtls_ssl_config conf;

    // 初始化SSL上下文和配置
    mbedtls_ssl_init(&ssl);
    mbedtls_ssl_config_init(&conf);

    // 配置SSL上下文
    mbedtls_ssl_setup(&ssl, &conf);

    // 设置调试回调函数
    mbedtls_ssl_conf_dbg(&conf, my_debug, stderr);

    // 设置调试级别
    mbedtls_debug_set_threshold(4); // 调试级别为4，最详细

    // 其他SSL/TLS配置和操作...

    return 0;
}


### 调试 `ssl_parse_certificate_chain` 函数

在 `ssl_parse_certificate_chain` 函数中添加调试信息：


int ssl_parse_certificate_chain(mbedtls_ssl_context *ssl, mbedtls_x509_crt *chain)
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    size_t i, n;
    uint8_t alert;

    MBEDTLS_SSL_DEBUG_MSG(2, ("Entering ssl_parse_certificate_chain"));

    if (ssl->in_msgtype != MBEDTLS_SSL_MSG_HANDSHAKE) {
        MBEDTLS_SSL_DEBUG_MSG(1, ("bad certificate message: in_msgtype = %d", ssl->in_msgtype));
        mbedtls_ssl_send_alert_message(ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                       MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE);
        return MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE;
    }

    if (ssl->in_msg[0] != MBEDTLS_SSL_HS_CERTIFICATE) {
        MBEDTLS_SSL_DEBUG_MSG(1, ("bad certificate message: in_msg[0] = %d", ssl->in_msg[0]));
        mbedtls_ssl_send_alert_message(ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                       MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE);
        return MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE;
    }

    // 其他解析证书链的代码...
    MBEDTLS_SSL_DEBUG_MSG(2, ("Successfully parsed certificate chain"));

    return 0;
}


### 调试 `ssl_parse_certificate_verify` 函数

在 `ssl_parse_certificate_verify` 函数中添加调试信息：


int ssl_parse_certificate_verify(mbedtls_ssl_context *ssl, int authmode,
                                 mbedtls_x509_crt *chain, void *rs_ctx)
{
    int ret;
    MBEDTLS_SSL_DEBUG_MSG(2, ("Entering ssl_parse_certificate_verify"));

    ret = mbedtls_x509_crt_verify(chain, ssl->session_negotiate->ca_chain,
                                  ssl->session_negotiate->ca_crl,
                                  ssl->session_negotiate->peer_cert,
                                  &ssl->session_negotiate->verify_result,
                                  ssl->conf->f_vrfy, ssl->conf->p_vrfy);

    if (ret != 0) {
        uint8_t alert;
        MBEDTLS_SSL_DEBUG_MSG(1, ("Certificate verification failed: ret = %d, verify_result = %d",
                                  ret, ssl->session_negotiate->verify_result));

        if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_OTHER) {
            alert = MBEDTLS_SSL_ALERT_MSG_ACCESS_DENIED;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_CN_MISMATCH) {
            alert = MBEDTLS_SSL_ALERT_MSG_BAD_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_KEY_USAGE) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_EXT_KEY_USAGE) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_NS_CERT_TYPE) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_BAD_PK) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_BAD_KEY) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_EXPIRED) {
            alert = MBEDTLS_SSL_ALERT_MSG_CERT_EXPIRED;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_REVOKED) {
            alert = MBEDTLS_SSL_ALERT_MSG_CERT_REVOKED;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_NOT_TRUSTED) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNKNOWN_CA;
        } else {
            alert = MBEDTLS_SSL_ALERT_MSG_CERT_UNKNOWN;
        }

        MBEDTLS_SSL_DEBUG_MSG(1, ("Sending alert message: alert = %d", alert));
        mbedtls_ssl_send_alert_message(ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL, alert);
    } else {
        MBEDTLS_SSL_DEBUG_MSG(2, ("Certificate verification succeeded"));
    }

    return ret;
}


### 运行调试

在运行你的程序时，确保调试级别设置为4，以便输出最详细的调试信息：


mbedtls_debug_set_threshold(4); // 设置调试级别为4，最详细


### 查看调试输出

运行你的程序后，调试信息将被输出到 `stderr`。你可以查看这些调试信息，了解 `ssl_parse_certificate_chain` 和 `ssl_parse_certificate_verify` 函数的执行流程和错误处理情况。例如：


ssl_tls.c:1234: Entering ssl_parse_certificate_chain
ssl_tls.c:1238: bad certificate message: in_msgtype = 22
ssl_tls.c:1242: bad certificate message: in_msg[0] = 11
ssl_tls.c:1250: Successfully parsed certificate chain
ssl_tls.c:1304: Entering ssl_parse_certificate_verify
ssl_tls.c:1310: Certificate verification failed: ret = -0x2700, verify_result = 0x0002
ssl_tls.c:1330: Sending alert message: alert = 46
ssl_tls.c:1340: Certificate verification succeeded


这些调试信息将帮助你理解函数的执行流程，并定位错误发生的位置和原因。
```

**user**: 

```
还是给你看下完整函数吧：
MBEDTLS_CHECK_RETURN_CRITICAL
static int ssl_parse_certificate_verify(mbedtls_ssl_context *ssl,
                                        int authmode,
                                        mbedtls_x509_crt *chain,
                                        void *rs_ctx)
{
    int ret = 0;
    const mbedtls_ssl_ciphersuite_t *ciphersuite_info =
        ssl->handshake->ciphersuite_info;
    int have_ca_chain = 0;

    int (*f_vrfy)(void *, mbedtls_x509_crt *, int, uint32_t *);
    void *p_vrfy;

    if (authmode == MBEDTLS_SSL_VERIFY_NONE) {
        return 0;
    }

    if (ssl->f_vrfy != NULL) {
        MBEDTLS_SSL_DEBUG_MSG(3, ("Use context-specific verification callback"));
        f_vrfy = ssl->f_vrfy;
        p_vrfy = ssl->p_vrfy;
    } else {
        MBEDTLS_SSL_DEBUG_MSG(3, ("Use configuration-specific verification callback"));
        f_vrfy = ssl->conf->f_vrfy;
        p_vrfy = ssl->conf->p_vrfy;
    }

    /*
     * Main check: verify certificate
     */
#if defined(MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK)
    if (ssl->conf->f_ca_cb != NULL) {
        ((void) rs_ctx);
        have_ca_chain = 1;

        MBEDTLS_SSL_DEBUG_MSG(3, ("use CA callback for X.509 CRT verification"));
        ret = mbedtls_x509_crt_verify_with_ca_cb(
            chain,
            ssl->conf->f_ca_cb,
            ssl->conf->p_ca_cb,
            ssl->conf->cert_profile,
            ssl->hostname,
            &ssl->session_negotiate->verify_result,
            f_vrfy, p_vrfy);
    } else
#endif /* MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK */
    {
        mbedtls_x509_crt *ca_chain;
        mbedtls_x509_crl *ca_crl;

#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
        if (ssl->handshake->sni_ca_chain != NULL) {
            ca_chain = ssl->handshake->sni_ca_chain;
            ca_crl   = ssl->handshake->sni_ca_crl;
        } else
#endif
        {
            ca_chain = ssl->conf->ca_chain;
            ca_crl   = ssl->conf->ca_crl;
        }

        if (ca_chain != NULL) {
            have_ca_chain = 1;
        }

        ret = mbedtls_x509_crt_verify_restartable(
            chain,
            ca_chain, ca_crl,
            ssl->conf->cert_profile,
            ssl->hostname,
            &ssl->session_negotiate->verify_result,
            f_vrfy, p_vrfy, rs_ctx);
    }

    if (ret != 0) {
        MBEDTLS_SSL_DEBUG_RET(1, "x509_verify_cert", ret);
    }

#if defined(MBEDTLS_SSL_ECP_RESTARTABLE_ENABLED)
    if (ret == MBEDTLS_ERR_ECP_IN_PROGRESS) {
        return MBEDTLS_ERR_SSL_CRYPTO_IN_PROGRESS;
    }
#endif

    /*
     * Secondary checks: always done, but change 'ret' only if it was 0
     */

#if defined(MBEDTLS_PK_HAVE_ECC_KEYS)
    {
        const mbedtls_pk_context *pk = &chain->pk;

        /* If certificate uses an EC key, make sure the curve is OK.
         * This is a public key, so it can't be opaque, so can_do() is a good
         * enough check to ensure pk_ec() is safe to use here. */
        if (mbedtls_pk_can_do(pk, MBEDTLS_PK_ECKEY)) {
            /* and in the unlikely case the above assumption no longer holds
             * we are making sure that pk_ec() here does not return a NULL
             */
            mbedtls_ecp_group_id grp_id = mbedtls_pk_get_ec_group_id(pk);
            if (grp_id == MBEDTLS_ECP_DP_NONE) {
                MBEDTLS_SSL_DEBUG_MSG(1, ("invalid group ID"));
                return MBEDTLS_ERR_SSL_INTERNAL_ERROR;
            }
            if (mbedtls_ssl_check_curve(ssl, grp_id) != 0) {
                ssl->session_negotiate->verify_result |=
                    MBEDTLS_X509_BADCERT_BAD_KEY;

                MBEDTLS_SSL_DEBUG_MSG(1, ("bad certificate (EC key curve)"));
                if (ret == 0) {
                    ret = MBEDTLS_ERR_SSL_BAD_CERTIFICATE;
                }
            }
        }
    }
#endif /* MBEDTLS_PK_HAVE_ECC_KEYS */

    if (mbedtls_ssl_check_cert_usage(chain,
                                     ciphersuite_info,
                                     !ssl->conf->endpoint,
                                     &ssl->session_negotiate->verify_result) != 0) {
        MBEDTLS_SSL_DEBUG_MSG(1, ("bad certificate (usage extensions)"));
        if (ret == 0) {
            ret = MBEDTLS_ERR_SSL_BAD_CERTIFICATE;
        }
    }

    /* mbedtls_x509_crt_verify_with_profile is supposed to report a
     * verification failure through MBEDTLS_ERR_X509_CERT_VERIFY_FAILED,
     * with details encoded in the verification flags. All other kinds
     * of error codes, including those from the user provided f_vrfy
     * functions, are treated as fatal and lead to a failure of
     * ssl_parse_certificate even if verification was optional. */
    if (authmode == MBEDTLS_SSL_VERIFY_OPTIONAL &&
        (ret == MBEDTLS_ERR_X509_CERT_VERIFY_FAILED ||
         ret == MBEDTLS_ERR_SSL_BAD_CERTIFICATE)) {
        ret = 0;
    }

    if (have_ca_chain == 0 && authmode == MBEDTLS_SSL_VERIFY_REQUIRED) {
        MBEDTLS_SSL_DEBUG_MSG(1, ("got no CA chain"));
        ret = MBEDTLS_ERR_SSL_CA_CHAIN_REQUIRED;
    }

    if (ret != 0) {
        uint8_t alert;

        /* The certificate may have been rejected for several reasons.
           Pick one and send the corresponding alert. Which alert to send
           may be a subject of debate in some cases. */
        if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_OTHER) {
            alert = MBEDTLS_SSL_ALERT_MSG_ACCESS_DENIED;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_CN_MISMATCH) {
            alert = MBEDTLS_SSL_ALERT_MSG_BAD_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_KEY_USAGE) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_EXT_KEY_USAGE) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_NS_CERT_TYPE) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_BAD_PK) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_BAD_KEY) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_EXPIRED) {
            alert = MBEDTLS_SSL_ALERT_MSG_CERT_EXPIRED;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_REVOKED) {
            alert = MBEDTLS_SSL_ALERT_MSG_CERT_REVOKED;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_NOT_TRUSTED) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNKNOWN_CA;
        } else {
            alert = MBEDTLS_SSL_ALERT_MSG_CERT_UNKNOWN;
        }
        mbedtls_ssl_send_alert_message(ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                       alert);
    }

#if defined(MBEDTLS_DEBUG_C)
    if (ssl->session_negotiate->verify_result != 0) {
        MBEDTLS_SSL_DEBUG_MSG(3, ("! Certificate verification flags %08x",
                                  (unsigned int) ssl->session_negotiate->verify_result));
    } else {
        MBEDTLS_SSL_DEBUG_MSG(3, ("Certificate verification flags clear"));
    }
#endif /* MBEDTLS_DEBUG_C */

    return ret;
}
你觉得应该如何调试？我觉得应该关注ssl->session_negotiate->verify_result。
```

**assistant**: 

```
你提出的关注点非常正确。`ssl->session_negotiate->verify_result` 包含了证书验证的详细结果，是调试 `ssl_parse_certificate_verify` 函数的重要信息。我们可以通过添加调试信息来跟踪 `verify_result` 的值，以及函数中各个关键步骤的执行情况。

### 调试 `ssl_parse_certificate_verify` 函数

以下是添加了详细调试信息的 `ssl_parse_certificate_verify` 函数：


MBEDTLS_CHECK_RETURN_CRITICAL
static int ssl_parse_certificate_verify(mbedtls_ssl_context *ssl,
                                        int authmode,
                                        mbedtls_x509_crt *chain,
                                        void *rs_ctx)
{
    int ret = 0;
    const mbedtls_ssl_ciphersuite_t *ciphersuite_info =
        ssl->handshake->ciphersuite_info;
    int have_ca_chain = 0;

    int (*f_vrfy)(void *, mbedtls_x509_crt *, int, uint32_t *);
    void *p_vrfy;

    MBEDTLS_SSL_DEBUG_MSG(2, ("Entering ssl_parse_certificate_verify"));

    if (authmode == MBEDTLS_SSL_VERIFY_NONE) {
        MBEDTLS_SSL_DEBUG_MSG(2, ("Auth mode is VERIFY_NONE, skipping verification"));
        return 0;
    }

    if (ssl->f_vrfy != NULL) {
        MBEDTLS_SSL_DEBUG_MSG(3, ("Use context-specific verification callback"));
        f_vrfy = ssl->f_vrfy;
        p_vrfy = ssl->p_vrfy;
    } else {
        MBEDTLS_SSL_DEBUG_MSG(3, ("Use configuration-specific verification callback"));
        f_vrfy = ssl->conf->f_vrfy;
        p_vrfy = ssl->conf->p_vrfy;
    }

    /*
     * Main check: verify certificate
     */
#if defined(MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK)
    if (ssl->conf->f_ca_cb != NULL) {
        ((void) rs_ctx);
        have_ca_chain = 1;

        MBEDTLS_SSL_DEBUG_MSG(3, ("use CA callback for X.509 CRT verification"));
        ret = mbedtls_x509_crt_verify_with_ca_cb(
            chain,
            ssl->conf->f_ca_cb,
            ssl->conf->p_ca_cb,
            ssl->conf->cert_profile,
            ssl->hostname,
            &ssl->session_negotiate->verify_result,
            f_vrfy, p_vrfy);
    } else
#endif /* MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK */
    {
        mbedtls_x509_crt *ca_chain;
        mbedtls_x509_crl *ca_crl;

#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
        if (ssl->handshake->sni_ca_chain != NULL) {
            ca_chain = ssl->handshake->sni_ca_chain;
            ca_crl   = ssl->handshake->sni_ca_crl;
            MBEDTLS_SSL_DEBUG_MSG(3, ("Using SNI-specific CA chain and CRL"));
        } else
#endif
        {
            ca_chain = ssl->conf->ca_chain;
            ca_crl   = ssl->conf->ca_crl;
            MBEDTLS_SSL_DEBUG_MSG(3, ("Using default CA chain and CRL"));
        }

        if (ca_chain != NULL) {
            have_ca_chain = 1;
        }

        ret = mbedtls_x509_crt_verify_restartable(
            chain,
            ca_chain, ca_crl,
            ssl->conf->cert_profile,
            ssl->hostname,
            &ssl->session_negotiate->verify_result,
            f_vrfy, p_vrfy, rs_ctx);
    }

    if (ret != 0) {
        MBEDTLS_SSL_DEBUG_RET(1, "x509_verify_cert", ret);
    }

#if defined(MBEDTLS_SSL_ECP_RESTARTABLE_ENABLED)
    if (ret == MBEDTLS_ERR_ECP_IN_PROGRESS) {
        MBEDTLS_SSL_DEBUG_MSG(2, ("ECP operation in progress"));
        return MBEDTLS_ERR_SSL_CRYPTO_IN_PROGRESS;
    }
#endif

    /*
     * Secondary checks: always done, but change 'ret' only if it was 0
     */

#if defined(MBEDTLS_PK_HAVE_ECC_KEYS)
    {
        const mbedtls_pk_context *pk = &chain->pk;

        /* If certificate uses an EC key, make sure the curve is OK.
         * This is a public key, so it can't be opaque, so can_do() is a good
         * enough check to ensure pk_ec() is safe to use here. */
        if (mbedtls_pk_can_do(pk, MBEDTLS_PK_ECKEY)) {
            /* and in the unlikely case the above assumption no longer holds
             * we are making sure that pk_ec() here does not return a NULL
             */
            mbedtls_ecp_group_id grp_id = mbedtls_pk_get_ec_group_id(pk);
            if (grp_id == MBEDTLS_ECP_DP_NONE) {
                MBEDTLS_SSL_DEBUG_MSG(1, ("invalid group ID"));
                return MBEDTLS_ERR_SSL_INTERNAL_ERROR;
            }
            if (mbedtls_ssl_check_curve(ssl, grp_id) != 0) {
                ssl->session_negotiate->verify_result |=
                    MBEDTLS_X509_BADCERT_BAD_KEY;

                MBEDTLS_SSL_DEBUG_MSG(1, ("bad certificate (EC key curve)"));
                if (ret == 0) {
                    ret = MBEDTLS_ERR_SSL_BAD_CERTIFICATE;
                }
            }
        }
    }
#endif /* MBEDTLS_PK_HAVE_ECC_KEYS */

    if (mbedtls_ssl_check_cert_usage(chain,
                                     ciphersuite_info,
                                     !ssl->conf->endpoint,
                                     &ssl->session_negotiate->verify_result) != 0) {
        MBEDTLS_SSL_DEBUG_MSG(1, ("bad certificate (usage extensions)"));
        if (ret == 0) {
            ret = MBEDTLS_ERR_SSL_BAD_CERTIFICATE;
        }
    }

    /* mbedtls_x509_crt_verify_with_profile is supposed to report a
     * verification failure through MBEDTLS_ERR_X509_CERT_VERIFY_FAILED,
     * with details encoded in the verification flags. All other kinds
     * of error codes, including those from the user provided f_vrfy
     * functions, are treated as fatal and lead to a failure of
     * ssl_parse_certificate even if verification was optional. */
    if (authmode == MBEDTLS_SSL_VERIFY_OPTIONAL &&
        (ret == MBEDTLS_ERR_X509_CERT_VERIFY_FAILED ||
         ret == MBEDTLS_ERR_SSL_BAD_CERTIFICATE)) {
        MBEDTLS_SSL_DEBUG_MSG(2, ("Verification failed but auth mode is OPTIONAL, ignoring error"));
        ret = 0;
    }

    if (have_ca_chain == 0 && authmode == MBEDTLS_SSL_VERIFY_REQUIRED) {
        MBEDTLS_SSL_DEBUG_MSG(1, ("got no CA chain"));
        ret = MBEDTLS_ERR_SSL_CA_CHAIN_REQUIRED;
    }

    if (ret != 0) {
        uint8_t alert;

        /* The certificate may have been rejected for several reasons.
           Pick one and send the corresponding alert. Which alert to send
           may be a subject of debate in some cases. */
        if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_OTHER) {
            alert = MBEDTLS_SSL_ALERT_MSG_ACCESS_DENIED;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_CN_MISMATCH) {
            alert = MBEDTLS_SSL_ALERT_MSG_BAD_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_KEY_USAGE) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_EXT_KEY_USAGE) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_NS_CERT_TYPE) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_BAD_PK) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_BAD_KEY) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_EXPIRED) {
            alert = MBEDTLS_SSL_ALERT_MSG_CERT_EXPIRED;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_REVOKED) {
            alert = MBEDTLS_SSL_ALERT_MSG_CERT_REVOKED;
        } else if (ssl->session_negotiate->verify_result & MBEDTLS_X509_BADCERT_NOT_TRUSTED) {
            alert = MBEDTLS_SSL_ALERT_MSG_UNKNOWN_CA;
        } else {
            alert = MBEDTLS_SSL_ALERT_MSG_CERT_UNKNOWN;
        }
        MBEDTLS_SSL_DEBUG_MSG(1, ("Sending alert message: alert = %d", alert));
        mbedtls_ssl_send_alert_message(ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                       alert);
    }

#if defined(MBEDTLS_DEBUG_C)
    if (ssl->session_negotiate->verify_result != 0) {
        MBEDTLS_SSL_DEBUG_MSG(3, ("! Certificate verification flags %08x",
                                  (unsigned int) ssl->session_negotiate->verify_result));
    } else {
        MBEDTLS_SSL_DEBUG_MSG(3, ("Certificate verification flags clear"));
    }
#endif /* MBEDTLS_DEBUG_C */

    MBEDTLS_SSL_DEBUG_MSG(2, ("Exiting ssl_parse_certificate_verify with ret = %d", ret));
    return ret;
}


### 关键调试信息

1. **进入和退出函数**：
   - `MBEDTLS_SSL_DEBUG_MSG(2, ("Entering ssl_parse_certificate_verify"));`
   - `MBEDTLS_SSL_DEBUG_MSG(2, ("Exiting ssl_parse_certificate_verify with ret = %d", ret));`

2. **使用的验证回调**：
   - `MBEDTLS_SSL_DEBUG_MSG(3, ("Use context-specific verification callback"));`
   - `MBEDTLS_SSL_DEBUG_MSG(3, ("Use configuration-specific verification callback"));`

3. **CA链和CRL的使用**：
   - `MBEDTLS_SSL_DEBUG_MSG(3, ("Using SNI-specific CA chain and CRL"));`
   - `MBEDTLS_SSL_DEBUG_MSG(3, ("Using default CA chain and CRL"));`

4. **证书验证结果**：
   - `MBEDTLS_SSL_DEBUG_RET(1, "x509_verify_cert", ret);`
   - `MBEDTLS_SSL_DEBUG_MSG(3, ("! Certificate verification flags %08x", (unsigned int) ssl->session_negotiate->verify_result));`
   - `MBEDTLS_SSL_DEBUG_MSG(3, ("Certificate verification flags clear"));`

5. **发送警报消息**：
   - `MBEDTLS_SSL_DEBUG_MSG(1, ("Sending alert message: alert = %d", alert));`

### 运行调试

确保调试级别设置为4，以便输出最详细的调试信息：


mbedtls_debug_set_threshold(4); // 设置调试级别为4，最详细


### 查看调试输出

运行你的程序后，调试信息将被输出到 `stderr`。你可以查看这些调试信息，了解 `ssl_parse_certificate_verify` 函数的执行流程和错误处理情况。例如：


ssl_tls.c:1234: Entering ssl_parse_certificate_verify
ssl_tls.c:1240: Use configuration-specific verification callback
ssl_tls.c:1250: Using default CA chain and CRL
ssl_tls.c:1260: x509_verify_cert() returned -0x2700
ssl_tls.c:1270: ! Certificate verification flags 00000001
ssl_tls.c:1280: Sending alert message: alert = 46
ssl_tls.c:1290: Exiting ssl_parse_certificate_verify with ret = -0x2700


这些调试信息将帮助你理解函数的执行流程，并定位错误发生的位置和原因。特别是 `ssl->session_negotiate->verify_result` 的值，它会告诉你证书验证失败的具体原因。
```



--------------------


<a href="https://chatboxai.app" style="display: flex; align-items: center;">
<img src='https://chatboxai.app/icon.png' style='width: 40px; height: 40px; padding-right: 6px'>
<b style='font-size:30px'>Chatbox AI</b>
</a>
