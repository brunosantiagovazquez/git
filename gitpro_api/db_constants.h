//DB NAME
#define DB_NAME "gitpro.db"

//PUBLIC ROLE
#define PUBLIC "PUBLIC"

//SQL ALL
#define ALL "*"

//TABLE NAMES
#define ROLE_TABLE "GP_ROL"
#define TASK_TABLE "GP_TAREA"
#define USER_TABLE "GP_USUARIO"
#define FILE_TABLE "GP_ARCHIVO"
#define ASOC_TABLE "GP_ASOCIACIONES"
#define ASIG_TABLE "GP_ASIGNACIONES"

//ROLE TABLE COLUMN NAMES
#define ROLE_NAME "NOMBRE_ROL"
#define CREATE_ROLE "CREAR_ROL"
#define ASSIGN_ROLE "ASIGNAR_ROL"
#define READ_TASK "CONSULTAR_TAREA"
#define ASSIGN_TASK "ASIGNAR_TAREA"
#define UPDATE_TASK "ACTUALIZAR_TAREA"
#define LINK_FILES  "ASOCIAR_ARCHIVOS"
#define REMOVE_TASK "BORRAR_TAREA"
#define CREATE_TASK "CREAR_TAREA"
#define REMOVE_ROLE "BORRAR_ROL"
#define UPDATE_ROLE "ACTUALIZAR_ROL"

//TASK TABLE COLUMN NAMES
#define TASK_ID "ID"
#define TASK_NAME "NOMBRE_TAREA"
#define TASK_STATE "ESTADO"
#define TASK_DESCRIP "DESCRIPCION"
#define TASK_NOTES "NOTAS"
#define TASK_START_EST "FECHA_INICIO_ESTIMADA"
#define TASK_END_EST "FECHA_FINAL_ESTIMADA"
#define TASK_START_REAL "FECHA_INICIO_REAL"
#define TASK_END_REAL "FECHA_FINAL_REAL"
#define TASK_PRIOR "PRIORIDAD"
#define TASK_TYPE "TIPO"
#define TASK_REALTIME "TIEMPO_REAL_MIN"
#define TASK_APROXTIME "TIEMPO_ESTIMADO_MIN"

//USER TABLE COLUMN NAMES
#define USER_NAME "NOMBRE_USUARIO"
#define USER_ROLE "NOMBRE_ROL_USUARIO"

//FILE TABLE COLUMN NAMES
#define FILE_NAME "NOMBRE_ARCHIVO"
#define FILE_PATH "RUTA_ARCHIVO"

//FILE ASOCIATIONS TO TASK NAMES
#define ASOC_PATH "RUTA_ARCHIVO_ASOC"
#define ASOC_TASK_ID "ID_ASOC"

//ASIGNED USERS TO TASK NAMES
#define ASIG_USER_NAME "NOMBRE_USUARIO_ASIG"
#define ASIG_TASK_ID "ID_ASIG"
