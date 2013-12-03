# Servidor principal

## ¿Cómo se usa?

### ¿Cómo se inicializa?

Llamando desde consola con el parámetro del puerto:

    # Suponiendo que el ejecutable está en ./bin/server y
    # queremos 1025 como puerto
    ./bin/server 1025

### ¿Cómo se obtiene información de él?

Se puede hacer una petición de 2 formas para la IP: con IP (en notación
de punto, ip) y sin IP (dando una 'semilla', ip-id para la IP privada);
y de 3 maneras: por hosts totales, por hosts por subred y por subredes.
Se puede pedir información del subnetting o calcular una subred.

#### Información de subnetting

##### Formato que regresa

    <ip> <class> <subnet-bits> <total-subnets>

##### Listado de peticiones posibles

    info-by-ip-and-hosts <ip> <total-hosts>
    info-by-ip-and-hosts-per-subnet <ip> <hosts-per-subnet>
    info-by-ip-and-subnets <ip> <subnets>
    info-by-hosts <ip-id> <total-hosts>
    info-by-hosts-per-subnet <ip-id> <hosts-per-subnet>
    info-by-subnets <ip-id> <subnets>

#### Cálculo de subred

##### Formato que regresa

    <subnet-num> (yes|no) <id> <broadcast> <mask> <host-end> <host-start>

##### Listado de peticiones posibles

    subnetting-by-ip-and-hosts <ip> <total-hosts> <subnet-id>
    subnetting-by-ip-and-hosts-per-subnet <ip> <hosts-per-subnet> <subnet-id>
    subnetting-by-ip-and-subnets <ip> <subnets> <subnet-id>
    subnetting-by-hosts <ip-id> <total-hosts> <subnet-id>
    subnetting-by-hosts-per-subnet <ip-id> <hosts-per-subnet> <subnet-id>
    subnetting-by-subnets subnets <ip-id> <subnet-id>

