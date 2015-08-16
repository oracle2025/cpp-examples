#CPP Examples

##simpleserver

Easily run a TCP Server based on boost asio like this:

```cpp
TCPServer server(portno, [](){return "Hello World\n";}); server.run();
```

