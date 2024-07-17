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



--------------------


<a href="https://chatboxai.app" style="display: flex; align-items: center;">
<img src='https://chatboxai.app/icon.png' style='width: 40px; height: 40px; padding-right: 6px'>
<b style='font-size:30px'>Chatbox AI</b>
</a>
