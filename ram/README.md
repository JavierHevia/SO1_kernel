# Modulo MEMORIA

Modulo que muestra la informacion del estado de la memria del sistema.

Compilar archivo

```
make all
```

Insertar modulo
```
sudo insmod memo_201313898.ko
```

Verificar mensaje de insersion
```
dmesg
```


Verificar informacion de los procesos en el directorio proc/
```
cd /proc/
```

Para saber todos los procesos que existen deberìa de aparecer en el primer lugar
```
lsmod
```

Obtener los mensajes de entrada y salida del modulo
```
dmesg
```

Obtener el archivo que se debiò escribir
```
cat memo_201010425_201313898
```

Para eliminar el modulo 
```
sudo rmmod memo_201313898
```

Se deberia abrir el archivo con la informacion del PID, Nombre y Estado de los procesos que estan corriendo en el sistema.


## Descripcion del Codigo

Se consulta el struct sysinfo que nos proporciona linux para poder saber el uso de memoria del sistema operativo, ya teniendo la informaciòn proporcionamos los datos de memoria total, memoria libre y porcentaje de memoria usada.



## License

Bajo licencia GLP.

