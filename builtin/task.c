#include <stdio.h>
#include <string.h>
#include "builtin.h"
#include "parse-options.h"
#include "../gitpro_api/gitpro_data_api.h"
#include "../gitpro_role_check/check_role.h"

#define OUT stdout
#define ERR stderr
#define IN stdin

#define MAX_BUFFER_SIZE 200

/* Usage message */
static const char * const builtin_task_usage[] =
{
	"task [-c | -r | -u | -d | -a | -l ]\n\tSome use examples:\n\t -c -n name -s state -d description --notes=\"my observations\" --est_start dd/mm/yyyy --est_end dd/mm/yyyy --start dd/mm/yyyy --end dd/mm/yyyy -p priority -t type --est_time mins --time mins\n\t\t(only required name, state, priority and type)\n\t -r -i id\n\t -u -n name -s state -d description --notes=\"my observations\" --est_start dd/mm/yyyy --est_end dd/mm/yyyy --start dd/mm/yyyy --end dd/mm/yyyy -p priority -t type --est_time mins --time mins\n\t -d -s state\n\t -a -i id --user --add=\"user1 ... userN\" --rm=\"user1 ... userN\"\n\t -l -i id --file --add=\"file1 ... fileN\" --rm=\"file1 ... fileN\"",
	NULL
};

/* Creates a new task */
void create_task();

/* Link or unlink a list of files and folders to a given task */ 
void link_task();

/* Assign or unassign a list of users to a given task */
void assign_task();

/* Remove an existent task */
void delete_task();

/* Update different values of a task */
void update_task();

/* Makes a filtered search of tasks on depending given parameters */
void read_task();


static int tcreate, tlink, tassign, tdelete, tupdate, user, file, tread, all;
static char *add = NULL;
static char *rm = NULL;
static char *task_id = NULL;
static char *task_name = NULL;
static char *task_state = NULL;
static char *task_desc = NULL;
static char *task_notes = NULL;
static char *task_est_start = NULL;
static char *task_est_end = NULL;
static char *task_start = NULL;
static char *task_end = NULL;
static char *task_prior = NULL;
static char *task_type = NULL;
static char *task_est_time = NULL;
static char *task_time = NULL;

static char *filter_task_id = NULL;
static char *filter_task_name = NULL;
static char *filter_task_state = NULL;
//static char *filter_task_desc = NULL;
//static char *filter_task_notes = NULL;
static char *filter_task_est_start = NULL;
static char *filter_task_est_end = NULL;
static char *filter_task_start = NULL;
static char *filter_task_end = NULL;
static char *filter_task_prior = NULL;
static char *filter_task_type = NULL;
static char *filter_task_est_time = NULL;
static char *filter_task_time = NULL;

void dealloc_filters(){
	free(filter_task_id);
	free(filter_task_name);
	free(filter_task_state);
	free(filter_task_est_start);
	free(filter_task_est_end);
	free(filter_task_start);
	free(filter_task_end);
	free(filter_task_prior);
	free(filter_task_type);
	free(filter_task_est_time);
	free(filter_task_time);
}

void receive_update_filters(char **id,char **name,char **state,char **est_start,char **est_end,
					char **start,char **end,char **prior,char **type,char **est_time,
					char **time){
	(*id) = (char *) malloc(MAX_BUFFER_SIZE);
	(*name) = (char *) malloc(MAX_BUFFER_SIZE);
	(*state) = (char *) malloc(MAX_BUFFER_SIZE);
	(*est_start) = (char *) malloc(MAX_BUFFER_SIZE);
	(*est_end) = (char *) malloc(MAX_BUFFER_SIZE);
	(*start) = (char *) malloc(MAX_BUFFER_SIZE);
	(*end) = (char *) malloc(MAX_BUFFER_SIZE);
	(*prior) = (char *) malloc(MAX_BUFFER_SIZE);
	(*type) = (char *) malloc(MAX_BUFFER_SIZE);
	(*est_time) = (char *) malloc(MAX_BUFFER_SIZE);
	(*time) = (char *) malloc(MAX_BUFFER_SIZE);
		
	fputs(_("All filters are by equality"),OUT);
	fputs(_("\ntask id: "),OUT);
	fgets((*id),MAX_BUFFER_SIZE,IN);
	fputs(_("task name: "),OUT);
	fgets((*name),MAX_BUFFER_SIZE,IN);
	fputs(_("task state: "),OUT);
	fgets((*state),MAX_BUFFER_SIZE,IN);
	fputs(_("task estimated start date: "),OUT);
	fgets((*est_start),MAX_BUFFER_SIZE,IN);
	fputs(_("task estimated end date: "),OUT);
	fgets((*end),MAX_BUFFER_SIZE,IN);
	fputs(_("task real start date: "),OUT);
	fgets((*start),MAX_BUFFER_SIZE,IN);
	fputs(_("task real end date: "),OUT);
	fgets((*end),MAX_BUFFER_SIZE,IN);
	fputs(_("task priority: "),OUT);
	fgets((*prior),MAX_BUFFER_SIZE,IN);
	fputs(_("task type: "),OUT);
	fgets((*type),MAX_BUFFER_SIZE,IN);
	fputs(_("task estimated time in minutes: "),OUT);
	fgets((*est_time),MAX_BUFFER_SIZE,IN);
	fputs(_("task real time in minutes: "),OUT);
	fgets((*time),MAX_BUFFER_SIZE,IN);
}

/* Main code of task command */
int cmd_task(int argc, const char **argv, const char *prefix){

	/* Options command struct */
	static struct option builtin_task_options[] = {
		OPT_GROUP("Task options"),
		OPT_BOOL('c',"create",&tcreate,N_("creates new task")),
		OPT_BOOL('l',"link",&tlink,N_("asociates files to a given task")),
		OPT_BOOL('a',"assign",&tassign,N_("assigns an user or list of users to a given task")),
		OPT_BOOL('r',"read",&tread,N_("show tasks that matchs with given parameters")),
		OPT_BOOL('d',"delete",&tdelete,N_("delete tasks that matchs with given filters")),
		OPT_BOOL('u',"update",&tupdate,N_("updates task data")),
		OPT_BOOL(0,"user",&user,N_("indicates that follows user names to add or remove task assignations")),
		OPT_BOOL(0,"all",&all,N_("reference to all existent tasks")),
		OPT_BOOL(0,"file",&file,N_("indicates that follows file names to add or remove task asociations")),
		OPT_GROUP("Link and Assign options"),
		OPT_STRING(0,"add",&add,"data1,data2 ... dataN",N_("option to add files or users to a given task")),
		OPT_STRING(0,"rm",&rm,"data1,data2 ... dataN",N_("option to remove files or usert to a given task")),
		OPT_GROUP("Task parameters"),
		OPT_STRING('i',"id",&task_id,"task id",N_("specifies task id")),		
		OPT_STRING('n',"name",&task_name,"task name",N_("specifies task name")),
		OPT_STRING('s',"state",&task_state,"task state",N_("specifies task state")),
		OPT_STRING('d',"desc",&task_desc,"task description",N_("specifies task description")),
		OPT_STRING(0,"notes",&task_notes,"task notes",N_("specifies task observations")),
		OPT_STRING(0,"est_start",&task_est_start,"task est start",N_("specifies estimated task start date")),
		OPT_STRING(0,"est_end",&task_est_end,"task est end",N_("specifies estimated task end date")),
		OPT_STRING(0,"start",&task_start,"task real start",N_("specifies real task start date")),
		OPT_STRING(0,"end",&task_end,"task real end",N_("specifies real task end date")),
		OPT_STRING('p',"prior",&task_prior,"task priority",N_("specifies task priority")),
		OPT_STRING('t',"type",&task_type,"task type",N_("specifies task type")),
		OPT_STRING(0,"est_time",&task_est_time,"task est time",N_("specifies estimated task time in minutes")),
		OPT_STRING(0,"time",&task_time,"task real time",N_("specifies real task time in minutes")),
		OPT_GROUP("Notes"),
		OPT_GROUP("\t- When updating tasks indicated data such as notes, estimated time and real time will be added to existent value\n\t- Date format is dd/mm/yyyy\n\t- Times are measured in minutes\n\t- If any filter is set when requested it apply to all existent tasks\n\t- To create a new task parameters name, state, priority and type are mandatory"),
		OPT_END()
	};

	/* Check if username is configured */
	char *uname = get_username();
	if(uname==NULL){
		fputs("Use git config --global user.name your_name to configure name and let them know to administrator\n",ERR);
		return 0;
	}
	
	/* Check if role has been assigned to user */
	char *urole = get_role(uname);
	if(urole==NULL){
		fputs("You haven't been assigned a role.\n",ERR);
		free(uname);
		return 0;
	}

/* START [1.7] Receive data process */
	argc = parse_options(argc, argv, prefix, builtin_task_options, builtin_task_usage, 0);

	
	/* More than one option selected at time */
	if(tcreate + tlink + tassign + tdelete + tupdate + tread > 1 ){
		fputs(_("Only one option at time\n"),ERR);
	}else {

		/* Check role permissions to do selected action */
		if( (tcreate && !can_create_task(urole)) 
			|| (tread && !can_read_task(urole))
			|| (tassign && !can_assign_task(urole))
			|| (tupdate && !can_update_task(urole))
			|| (tlink && !can_link_files(urole))
			|| (tdelete && !can_remove_task(urole)) ){
			fputs("You haven't enought permissions to do this action.\n",ERR);
			free(uname);
			free(urole);		
			return 0;
		}
		free(uname);
		free(urole);
		
		/* Receive filter data if delete, update or read tasks is set */
		if(tdelete || tupdate || tread){
			receive_update_filters(&filter_task_id,&filter_task_name,&filter_task_state,
					&filter_task_est_start,&filter_task_est_end,&filter_task_start,
					&filter_task_end,&filter_task_prior,&filter_task_type,
					&filter_task_est_time,&filter_task_time);
		}
/* END [1.7] Receive data process */
		
		if(tcreate){
			/* Create task option */
			create_task();
		}else if(tlink){
			/* Link task option */
			link_task();
		}else if(tassign){
			/* Assign task option */
			assign_task();
		}else if(tdelete){
			/* Remove task option */
			delete_task();
		}else if(tupdate){
			/* Update task option */
			update_task();
		}else if(tread){
			/* Read task option */
			read_task();
		}else{
			/* No action defined */
			fputs(_("No action defined"),ERR);
			usage_with_options(builtin_task_usage,builtin_task_options);
			return 0;
		}
		
		/* Free filter data if delete, update or read tasks was set */
		if(tdelete || tupdate || tread){
			dealloc_filters();
		}
	}
	return 1;
}

void create_task(){
	fputs(_("Create task option\n"),OUT);
	if(task_name!=NULL && task_state!=NULL && task_prior!=NULL && task_type!=NULL){
		printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",task_name,task_state,
			task_desc,task_prior,task_type,task_notes,task_est_time,task_time,
			task_est_start,task_est_end,task_start,task_end);
	}
}

void link_task(){
	fputs(_("Link files to task option\n"),OUT);
	if(task_id!=NULL && file && (add!=NULL || rm!=NULL)){
		printf("%s\n%s\n%s\n",task_id,add,rm);
	}
}

void assign_task(){
	fputs(_("Assign users to task option\n"),OUT);
	if(task_id!=NULL && user && (add!=NULL || rm!=NULL)){
		printf("%s\n%s\n%s\n",task_id,add,rm);
	}
}

void delete_task(){
	fputs(_("Delete task option\n"),OUT);
	if(task_id!=NULL && task_name!=NULL && task_state!=NULL && task_desc!=NULL && 
		task_prior!=NULL && task_type!=NULL && task_notes!=NULL && task_est_time!=NULL && 
		task_time!=NULL && task_est_start!=NULL && task_est_end!=NULL && task_start!=NULL && 
		task_end!=NULL){
		printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",task_name,task_state,
			task_desc,task_prior,task_type,task_notes,task_est_time,task_time,
			task_est_start,task_est_end,task_start,task_end);
	}
}

void update_task(){
	fputs(_("Update task option\n"),OUT);
	if(task_id!=NULL && task_name!=NULL && task_state!=NULL && task_desc!=NULL && 
		task_prior!=NULL && task_type!=NULL && task_notes!=NULL && task_est_time!=NULL && 
		task_time!=NULL && task_est_start!=NULL && task_est_end!=NULL && task_start!=NULL && 
		task_end!=NULL){
		printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",task_id,task_name,task_state,
			task_desc,task_prior,task_type,task_notes,task_est_time,task_time,
			task_est_start,task_est_end,task_start,task_end);
	}
}

void read_task(){
	fputs(_("Read tasks option\n"),OUT);
	if(task_id!=NULL && task_name!=NULL && task_state!=NULL && task_desc!=NULL && 
		task_prior!=NULL && task_type!=NULL && task_notes!=NULL && task_est_time!=NULL && 
		task_time!=NULL && task_est_start!=NULL && task_est_end!=NULL && task_start!=NULL && 
		task_end!=NULL){
		printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",task_id,task_name,task_state,
			task_desc,task_prior,task_type,task_notes,task_est_time,task_time,
			task_est_start,task_est_end,task_start,task_end);
	}
}

