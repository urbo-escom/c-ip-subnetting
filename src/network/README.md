# BSD/Winsock sockets #

## ¿Qué es? ##

Se trata de una interfaz envolvente para los sockets de BSD y de Winsock.
Solo define las operaciones básicas para crear, asignar, escuchar,
conectar, recibir y enviar información de un stream socket.
Probablemente no sirva para múltiples conexiones entrantes.

## ¿Cómo se usa? ##

De forma parecida a un socket BSD o Winsock.

### Para un servidor ###

    ...
    Socket_T* socket = Socket_new(NULL, "2345");
    Socket_bind(socket);
    Socket_listen(socket, 10);
    Socket_accept(sock);
    
    Socket_receive(sock, msg, 20);
    Socket_send(sock, "hello", 5);
    ...
    Socket_get_ip(sock);
    Socket_get_port(sock);
    ...
    Socket_free(&sock);
    ...

### Para un cliente ###

    ...
    Socket_T* socket = Socket_new("127.0.0.1", "2345");
    Socket_connect(socket);
    Socket_timeout(socket, 20);
    Socket_send(sock "request", 7);
    Socket_receive(sock, msg, 65);
    ...
    Socket_free(&sock);
    ...

