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

    info_by_ip_and_hosts <ip> <total-hosts>
    info_by_ip_and_hosts_per_subnet <ip> <hosts-per-subnet>
    info_by_ip_and_subnets <ip> <subnets>
    info_by_hosts <total-hosts> <ip-id>
    info_by_hosts_per_subnet <hosts-per-subnet> <ip-id>
    info_by_subnets <subnets> <ip-id>

#### Cálculo de subred

##### Formato que regresa

    <subnet-num> (yes|no) <id> <broadcast> <mask> <host-end> <host-start>

##### Listado de peticiones posibles

    subnetting_by_ip_and_hosts <ip> <total-hosts> <subnet-id>
    subnetting_by_ip_and_hosts_per_subnet <ip> <hosts-per-subnet> <subnet-id>
    subnetting_by_ip_and_subnets <ip> <subnets> <subnet-id>
    subnetting_by_hosts <total-hosts> <subnet-id> <ip-id>
    subnetting_by_hosts_per_subnet <hosts-per-subnet> <subnet-id> <ip-id>
    subnetting_by_subnets subnets <subnet-id> <ip-id>

