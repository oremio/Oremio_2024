# 1-Internet

## How does the internet work?

The Internet is a global network of computers connected to each other which communicate **through a standardized set of protocols**.

## [What is HTTP?](https://www.cloudflare.com/en-gb/learning/ddos/glossary/hypertext-transfer-protocol-http/)

HTTP is the TCP/IP based application layer communication protocol which standardizes how the client and server communicate with each other. HTTP follows a classical "Client-Server model" with a client opening a connection request, then waiting until it receives a response. **HTTP is a stateless protocol**, that means that the server does not keep any data (state) between two requests.

### What is in an HTTP request?

An HTTP request is the way Internet communications platforms such as web browsers ask for the information they need to load a website.

Each HTTP request made across the Internet carries with it a series of encoded data that carries different types of information. A typical HTTP request contains:

1. HTTP version type
2. a URL
3. an HTTP method
4. HTTP request headers
5. Optional HTTP body.

Let’s explore in greater depth how these requests work, and how the contents of a request can be used to share information.

### What is an HTTP method?

An HTTP method, sometimes referred to as an HTTP verb, indicates the action that the HTTP request expects from the queried server. For example, **two of the most common HTTP methods are ‘GET’ and ‘POST’**; a ‘GET’ request expects information back in return (usually in the form of a website), while a ‘POST’ request typically indicates that the client is submitting information to the web server (such as form information, e.g. a submitted username and password).

### What are HTTP request headers?

HTTP headers contain text information stored in key-value pairs, and they are included in every HTTP request (and response, more on that later). These headers communicate core information, such as what browser the client is using and what data is being requested.

Example of HTTP request headers from Google Chrome's network tab:

![HTTP request headers](https://www.cloudflare.com/img/learning/ddos/glossary/hypertext-transfer-protocol-http/http-request-headers.png)

### What is in an HTTP request body?

The body of a request is the part that contains the ‘body’ of information the request is transferring. The body of an HTTP request **contains any information being submitted to the web server**, such as a username and password, or any other data entered into a form.

### What is in an HTTP response?

An HTTP response is what web clients (often browsers) receive from an Internet server in answer to an HTTP request. These responses communicate valuable information based on what was asked for in the HTTP request.

A typical HTTP response contains:

1. an HTTP status code
2. HTTP response headers
3. optional HTTP body

### What’s an HTTP status code?

HTTP status codes are 3-digit codes most often used to indicate whether an HTTP request has been successfully completed. Status codes are broken into the following 5 blocks: 

1. 1xx Informational
2. 2xx Success
3. 3xx Redirection
4. 4xx Client Error
5. 5xx Server Error

The “xx” refers to different numbers between 00 and 99. 

Status codes starting with the number ‘2’ indicate a success. For example, after a client requests a webpage, the most commonly seen responses have a status code of ‘200 OK’, indicating that the request was properly completed. 

If the response starts with a ‘4’ or a ‘5’ that means there was an error and the webpage will not be displayed. A status code that begins with a ‘4’ indicates a client-side error (it is very common to encounter a ‘404 NOT FOUND’ status code when making a typo in a URL). A status code beginning in ‘5’ means something went wrong on the server side. Status codes can also begin with a ‘1’ or a ‘3’, which indicate an informational response and a redirect, respectively. 

### What are HTTP response headers?

Much like an HTTP request, an HTTP response comes with headers that convey important information such as the language and format of the data being sent in the response body. 

Example of HTTP response headers from Google Chrome's network tab: 

![HTTP response headers](https://www.cloudflare.com/img/learning/ddos/glossary/hypertext-transfer-protocol-http/http-response-headers.png)

### What is in an HTTP response body?

Successful HTTP responses to ‘GET’ requests generally have a body which contains the requested information. In most web requests, **this is HTML data** that a web browser will translate into a webpage. 

### Can DDoS attacks be launched over HTTP?

Keep in mind that HTTP is a “stateless” protocol, which means that each command runs independent of any other command. In the original spec, HTTP requests each created and closed a [TCP](https://www.cloudflare.com/learning/ddos/glossary/tcp-ip/) connection. In newer versions of the HTTP protocol (HTTP 1.1 and above), persistent connection allows for multiple HTTP requests to pass over a persistent TCP connection, improving resource consumption. In the context of [DoS](https://www.cloudflare.com/learning/ddos/glossary/denial-of-service/) or [DDoS attacks](https://www.cloudflare.com/learning/ddos/what-is-a-ddos-attack/), **HTTP requests in large quantities** can be used to mount an attack on a target device, and are considered part of application layer attacks or [layer 7](https://www.cloudflare.com/learning/ddos/what-is-layer-7/) attacks. 

### Extended reading

[An overview of HTTP](https://developer.mozilla.org/en-US/docs/Web/HTTP/Overview)

[Journey to HTTP/2](https://kamranahmed.info/blog/2016/08/13/http-in-depth)

[HTTP/3 From A To Z: Core Concepts](https://www.smashingmagazine.com/2021/08/http3-core-concepts-part1/)

[HTTP/3 Is Now a Standard: Why Use It and How to Get Started](https://thenewstack.io/http-3-is-now-a-standard-why-use-it-and-how-to-get-started/)https://thenewstack.io/http-3-is-now-a-standard-why-use-it-and-how-to-get-started/)

## [Browsers and how they work?](https://www.browserstack.com/guide/browser-rendering-engine)

Browser is pivotal in the functioning of any website. **Right from how the application renders to how it functions**, everything depends on the Browser and its functioning. Before diving into the role of a rendering engine in browsers, let’s quickly understand the underlying architecture of a web browser.

### Understanding the Architecture of Web Browsers

Browsers are built of FrontEnd and BackEnd. While the FrontEnd ensures how the webpage appears on the browser, the backend handles the requests and is the carrier of information. Its different components work in coordination to deliver a seamless web experience.

![Architecture of Web Browsers](https://browserstack.wpenginepowered.com/wp-content/uploads/2022/12/Architecture-of-Web-Browsers-700x564.png)

### Components of Web Browser

Web Browsers consist of **7 different components** listed below:

#### User Interface

This component allows end-users to interact with all visual elements available on the web page. The visual elements include the **address bar, home button, next button,** and all other elements that fetch and display the web page requested by the end-user.

#### Browser Engine

It is a core component of every web browser. The browser engine functions as an intermediary or a bridge between the user interface and the rendering engine. It **queries and handles the rendering engine** as per the inputs received from the user interface.

#### Rendering Engine

As the name suggests, this component is responsible for rendering a specific web page requested by the user on their screen. It interprets HTML and XML documents along with images that are styled or formatted using CSS, and a final layout is generated, which is displayed on the user interface.

**Note**: Every browser has its own unique rendering engine. Rendering engines might also differ for different browser versions. The list below mentions browser engines used by a few common browsers:

1. Google Chrome and Opera v.15+: **Blink**
2. Internet Explorer: **Trident**
3. Mozilla Firefox: **Gecko**
4. Chrome for iOS and Safari: **WebKit**

#### Networking

This component is responsible for **managing network calls** using standard protocols like HTTP or FTP. It also looks after security issues associated with internet communication.

#### JavaScript Interpreter

As the name suggests, it is responsible for **parsing and executing the JavaScript code** embedded in a website. Once the interpreted results are generated, they are forwarded to the rendering engine for display on the user interface.

#### UI Backend

This component **uses the user interface methods** of the underlying operating system. It is mainly used for drawing basic widgets (windows and combo boxes).

#### Data Storage/Persistence

It is a persistent layer. A web browser needs to store various types of data locally, for example, cookies. As a result, browsers must **be compatible with data storage mechanisms** such as WebSQL, IndexedDB, FileSystem, etc.

Now that we are aware of the key components involved in building a web browser let’s dig deep into the role of the rendering engine.

### Role of Rendering Engine

Once a user requests a particular document, the rendering engine starts fetching the content of the requested document. This is done via the networking layer. The rendering engine starts receiving the content of that specific document in chunks of 8 KBs from the networking layer. After this, the basic flow of the rendering engine begins.

![Browser rendering engine](https://browserstack.wpenginepowered.com/wp-content/uploads/2019/11/Screenshot-2019-11-12-at-3.26.19-PM.png)

The four basic steps include:

1. The requested HTML page is **parsed in chunks**, including the external CSS files and in style elements, by the rendering engine. The HTML elements are then converted into DOM nodes to form a **“content tree” or “DOM tree.”**
2. Simultaneously, the browser also creates a **render tree.** This tree includes both the styling information as well as the visual instructions that define the order in which the elements will be displayed. The render tree ensures that the content is displayed in the desired order.
3. Further, the render tree goes through the **layout process.** When a render tree is created, the position or size values are not assigned. *The entire process of calculating values for evaluating the desired position is called a layout process*. In this process, every node is assigned the exact coordinates. This ensures that every node appears at an accurate position on the screen.
4. The final step is to paint the screen, wherein the render tree is traversed, and the renderer’s **paint()** method is invoked, which paints each node on the screen using the UI backend layer.

By understanding how a rendering engine works, web developers can gain greater insight into how websites operate. Consequently, they can develop, design, and deploy content more efficiently. If one comprehends the nuance of how web content is displayed on a user’s screen by various browsers, one is simply more equipped to create content that is compatible with multiple browsers. 

### Extended reading

[How Browsers Work](https://www.html5rocks.com/en/tutorials/internals/howbrowserswork/)

[Populating the Page: How Browsers Work](https://developer.mozilla.org/en-US/docs/Web/Performance/How_browsers_work)

