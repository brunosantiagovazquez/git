#include "generic_list.h"

/* See specification in generic_list.h */
void insert_role(role_list *list,char *name,int create_role,int assign_role,
				int read_task,int assign_task,int update_task,int link_files,
				int remove_task,int create_task,int remove_role,int update_role){
	if((*list)==NULL){
	 	(*list) = (role_list) malloc(sizeof(struct role_node));
		(**list).role_name = strdup(name);
		(**list).create_role = create_role;
		(**list).assign_role = assign_role;
		(**list).read_task = read_task;
		(**list).assign_task = assign_task;
		(**list).update_task = update_task;
		(**list).link_files = link_files;
		(**list).remove_task = remove_task;
		(**list).create_task = create_task;
		(**list).remove_role = remove_role;
		(**list).update_role = update_role;
		(**list).next = NULL;
	}else{
		insert_role(&((*list)->next),name,create_role,assign_role,read_task,
					assign_task,update_task,link_files,remove_task,create_task,
					remove_role,update_role);
	}
}

/* See specification in generic_list.h */
void insert_task(task_list *list,int id,char *name,char *state,char *description,
				char *notes,char *type,char *priority,int real_time,int est_time){
	if((*list)==NULL){
	 	(*list) = (task_list) malloc(sizeof(struct task_node));
		//*******************************************************
		// 	FALTAN LAS FECHAS EN EL STRUCT, INSERTARLAS AQUÍ y cogerlas en el callback
		//*******************************************************
		(**list).task_id = id;		
		(**list).task_name = strdup(name);
		(**list).state = strdup(state);
		(**list).description = strdup(description);
		(**list).notes = strdup(notes);
		(**list).type = strdup(type);
		(**list).priority = strdup(priority);
		(**list).real_time_min = real_time;
		(**list).est_time_min = est_time;
		(**list).next = NULL;
	}else{
		insert_task(&((*list)->next),id,name,state,description,notes,
					type,priority,real_time,est_time);
	}
}

/* See specification in generic_list.h */
void insert_user(user_list *list,char *name,char *urole){
	if((*list)==NULL){
	 	(*list) = (user_list) malloc(sizeof(struct user_node));
		(**list).user_name = strdup(name);
		(**list).user_role = strdup(urole);
		(**list).next = NULL;
	}else{
		insert_user(&((*list)->next),name,urole);
	}
}

/* See specification in generic_list.h */
void insert_file(file_list *list,char *name,char *path){
	if((*list)==NULL){
	 	(*list) = (file_list) malloc(sizeof(struct file_node));
		(**list).file_name = strdup(name);
		(**list).file_path = strdup(path);		
		(**list).next = NULL;
	}else{
		insert_file(&((*list)->next),name,path);
	}
}

/* See specification in generic_list.h */
void insert_asoc(asoc_list *list,char *path,int task_id){
	if((*list)==NULL){
	 	(*list) = (asoc_list) malloc(sizeof(struct asoc_node));
		(**list).file_path = strdup(path);
		(**list).task_id = task_id;
		(**list).next = NULL;
	}else{
		insert_asoc(&((*list)->next),path,task_id);
	}
}

/* See specification in generic_list.h */
void insert_asig(asig_list *list,char *user_name,int task_id){
	if((*list)==NULL){
	 	(*list) = (asig_list) malloc(sizeof(struct asig_node));
		(**list).user_name = strdup(user_name);
		(**list).task_id = task_id;
		(**list).next = NULL;
	}else{
		insert_asig(&((*list)->next),user_name,task_id);
	}
}

/* See specification in generic_list.h */
void dealloc_roles(role_list list){
	role_list aux;	
	while(list!=NULL){
		aux = list;
		list=(*list).next;
		free((*aux).role_name);
		free(aux);
	}
}

/* See specification in generic_list.h */
void dealloc_tasks(task_list list){
	task_list aux;	
	while(list!=NULL){
		aux = list;
		list=(*list).next;
		free((*aux).task_name);
		free((*aux).state);
		free((*aux).description);
		free((*aux).notes);
		free((*aux).type);
		free((*aux).priority);
		free(aux);
	}
}

/* See specification in generic_list.h */
void dealloc_users(user_list list){
	user_list aux;	
	while(list!=NULL){
		aux = list;
		list=(*list).next;
		free((*aux).user_name);
		free((*aux).user_role);
		free(aux);
	}
}

/* See specification in generic_list.h */
void dealloc_files(file_list list){
	file_list aux;	
	while(list!=NULL){
		aux = list;
		list=(*list).next;
		free((*aux).file_name);
		free((*aux).file_path);
		free(aux);
	}
}

/* See specification in generic_list.h */
void dealloc_asocs(asoc_list list){
	asoc_list aux;	
	while(list!=NULL){
		aux = list;
		list=(*list).next;
		free((*aux).file_path);
		free(aux);
	}
}

/* See specification in generic_list.h */
void dealloc_asigs(asig_list list){
	asig_list aux;	
	while(list!=NULL){
		aux = list;
		list=(*list).next;
		free((*aux).user_name);
		free(aux);
	}
}