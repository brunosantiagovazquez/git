#include <string.h>
#include "builtin.h"
#include "parse-options.h"
#include "../gitpro_role_check/check_role.h"
#include "../gitpro_api/gitpro_data_api.h"

#define OUT stdout
#define ERR stderr

static const char * const builtin_role_usage[] =
{
	"role [-c | -r | -u | -d | -a]\n\tSome use examples:\n\t-c -n role_name -p 10_bit_array\n\t-r -n role_name\n\t-u -n role_name -p 10_bit_array\n\t-d -n role_name\n\t-a -n role_name -t --add=\"u1 u2 ... uN\" --rm=\"u1 u2 ... uN\"",
	NULL
};

void create_role();
void read_role();
void update_role();
void delete_role();
void assign_role();

static int rcreate, rupdate, rdelete, rread, rassign,user;
static char *role_name = NULL;
static char *perms = NULL;
static char *add = NULL;
static char *rm = NULL;

int cmd_role (int argc, const char **argv, const char *prefix){
	
	static struct option builtin_role_options[] = {
		OPT_GROUP("Role options"),
		OPT_BOOL('r',"read",&rread,N_("check role permissions")),		
		OPT_BOOL('c',"create",&rcreate,N_("creates new role")),
		OPT_BOOL('u',"update",&rupdate,N_("update given role")),		
		OPT_BOOL('d',"delete",&rdelete,N_("remove given role")),
		OPT_BOOL('a',"assign",&rassign,N_("assign role to user")),
		OPT_BOOL(0,"user",&user,N_("indicates that follows user names to add or remove role assignations")),
		OPT_GROUP("Role params"),
		OPT_STRING('n',"name",&role_name,"role name",N_("specifies role name")),
		OPT_STRING('p',"perms",&perms,"permissions",N_("specifies permissions in 10 array bit format")),
		//Format: --add="u1,u2...un"
		OPT_STRING(0,"add",&add,"user1, user2 ... userN",N_("specifies user name to add role assignation")),
		//Format: --rm="u1,u2...un"
		OPT_STRING(0,"rm",&rm,"user1, user2 ... userN",N_("specifies user name to remove role assignation")),
		//Permissions array bit info
		OPT_GROUP("Array bit format example: 10101010101"),
		OPT_GROUP("Array bit meaning"),
		OPT_GROUP("\tbits meaning from left to right\n\t create role\n\t remove role\n\t update role\n\t assign role\n\t create task\n\t read task\n\t update task\n\t delete task\n\t assign task\n\t link files"),
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

/* START [2.6] Receive data process */
	argc = parse_options(argc, argv, prefix, builtin_role_options, builtin_role_usage, 0);
/* END [2.6] Receive data process */	
	
	if( (rcreate + rread + rdelete + rupdate + rassign)  > 1){
		fputs(_("Only one option at time\n"),ERR);
		return 0;
	}else{

		if(!rread){
/* START [2.7] Control admin process */
			/* Check if is admin */
			int admin = is_admin(uname);
			if(!admin){
				/* Check role permissions to do selected action if haven't admin privileges */
				if( (rcreate && !can_create_role(urole)) 
					|| (rassign && !can_assign_role(urole))
					|| (rupdate && !can_update_role(urole))
					|| (rdelete && !can_remove_role(urole)) ){
					fputs("You haven't enought permissions to do this action.\n",ERR);
					free(uname);
					free(urole);		
					return 0;
				}
			}
			free(uname);
			free(urole);
/* END [2.7] Control admin process */
		}
		
		if(rcreate){
			/* Create role option */
			create_role();
		}else if(rread){
			/* Read role option */
			read_role();
		}else if(rupdate){
			/* Update role option */
			update_role();
		}else if(rdelete){
			/* Delete role option */
			delete_role();
		}else if(rassign){
			if(user){
				/* Assign role option */
				assign_role();
			}else{
				fputs(_("Wrong format, see usage of assign command\n"),ERR);
				
			}
		}else{
			/* No action defined */
			fputs(_("No action defined\n"),ERR);
			usage_with_options(builtin_role_usage,builtin_role_options);
			return 0;	
		}
	}
	
	return 1;	
}


void create_role(){
	fputs(_("Create role option\n"),OUT);
	if(role_name!=NULL && perms!=NULL){
		printf("%s\n%s\n",role_name,perms);
	}
}

void read_role(){
	fputs(_("Read role option\n"),OUT);
	if(role_name!=NULL && perms==NULL){
		printf("%s\n",role_name);
	}
}

void update_role(){
	fputs(_("Update role option\n"),OUT);
	if(role_name!=NULL && perms!=NULL){
		printf("%s\n%s\n",role_name,perms);
	}
}

void delete_role(){
	fputs(_("Delete role option\n"),OUT);
	if(role_name!=NULL && perms==NULL){
		printf("%s\n",role_name);
	}
}

void assign_role(){
	fputs(_("Assign role option\n"),OUT);
	if(role_name!=NULL && user && (add!=NULL || rm!=NULL)){
		printf("%s\n%s\n%s\n",role_name,add,rm);
	}
}
