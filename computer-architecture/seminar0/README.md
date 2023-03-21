# Seminar 0 - Introduction to the programming enviroment

Each user has a home in front-end node of atcgrid. There you can:

## Execute commands with a ssh client<br>

To execute commands in the remote node<br>
`ssh -X username@atcgrid.ugr.es`

Then you are asked for your password.
Once you are logged you are executing commands on remote.

To automate this process you can build this script:

```
#!/bin/bash

sshpass -p password ssh -x username@atcgrid.ugr.es`
```

## Upload and download files
To upload and download files to/from your node<br>
`sftp username@atcgrid.ugr.es`

As same as before, you are asked for the password.

An easier way to upload and download files is by mounting the remote home in your local directory.
This script mount the remote home:

```
#!/bin/bash

echo "password" | sshfs -o password_stdin username@atcgrid.ugr.es:/home/ac014 ~/local_directory
```

## ssh commands
Send to execute a job<br>
`srun arguments command`

Send to execute a script<br>
`sbatch`

The arguments: <br>
`p` specify a node <br>
`A` <br>
`n<number>` or `--ntasks=<number>` number of execution instances <br>
`c<number>` or `--cpus-per-task=<number>` number of cores assigned (default one core) <br>
`--hint=nomultithread` to not use logic cores, just physical cores (default logic cores) <br>
`--exclusive` execute just one process at the same time <br>
   
More commands: <br>
`squeue` shows all executing jobs and queued too <br>
`scancel jobid` removes "jobid" job <br>
`sinfo` list information of all partitions (queues) and nodes <br>
`sinfo -p node -o"%10D %10G %20b %f"` list the nodes (D), the resources (G) and the characteristics actives (b) and avaibles (f) in the specified partition (-p) (%[[.]size]type[suffix])

## Example
This is the code of [HelloOMP.c](./HelloOMP.c)

```
/**
 * 
 Compilar con gcc –O2 –fopenmp HelloOMP.c –o HelloOMP
 * 
 */

#include <stdio.h>
#include <omp.h>

int main(void) {

  #pragma omp parallel
    printf("(%d:!!!Hello world!!!)", 
             omp_get_thread_num());

  return(0);

}
```

The script to execute HelloOMP.c in atcgrid is [helloomp.sh](./helloomp.sh)

```
#!/bin/bash
#Órdenes para el Gestor de carga de trabajo (no intercalar instrucciones del scrip
#1. Asignar al trabajo un nombre
#SBATCH --job-name=helloOMP
#2. Asignar el trabajo a una partición (cola) 
#SBATCH --partition=ac 
#3. Asignar el trabajo a un account 
#SBATCH --account=ac
#4. Para que el trabajo no comparta recursos 
#SBATCH --exclusive
#5. Para que se genere un único proceso del sistema operativo que pueda usar un máximo de 12 núcleos
#SBATCH --ntasks 1 --cpus-per-task 12
#Se pueden añadir más órdenas para el gestor de colas

#Obtener información de las variables del entorno del Gestor de carga de trabajo:
echo "Id. usuario del trabajo: $SLURM_JOB_USER"
echo "Id. del trabajo: $SLURM_JOBID"
echo "Nombre del trabajo especificado por usuario: $SLURM_JOB_NAME"
echo "Directorio de trabajo (en el que se ejecuta el script): $SLURM_SUBMIT_DIR"
echo "Cola: $SLURM_JOB_PARTITION"
echo "Nodo que ejecuta este trabajo:$SLURM_SUBMIT_HOST"
echo "Nº de nodos asignados al trabajo: $SLURM_JOB_NUM_NODES"
echo "Nodos asignados al trabajo: $SLURM_JOB_NODELIST"
echo "CPUs por nodo: $SLURM_JOB_CPUS_PER_NODE"

export OMP_DYNAMIC=False

#Instrucciones del script para ejecutar código:
echo -e "\n 1. Ejecución helloOMP una vez sin cambiar nº de threads (valor por defecto)\n"
srun ./HelloOMP
echo -e "\n\n 2. Ejecución helloOMP varias veces con distinto nº de threads:\n" 
for ((P=12;P>0;P=P/2))
do
   #export OMP_NUM_THREADS=$P
   echo -e "  - Para $P threads:\n"
   srun --cpus-per-task=$P --hint nomultithread ./HelloOMP
done
```
