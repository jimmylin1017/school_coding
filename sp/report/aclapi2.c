#include <acl/libacl.h>
#include <sys/acl.h>
#include <unistd.h> /* getopt */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>

#define errExit(x) perror(x),exit(1)

void usageError(char *progName)
{
    fprintf(stderr, "Usage: %s [-d] filename\n", progName);
    exit(EXIT_FAILURE);
}

gid_t* groupIdFromName(char* groupName)
{
	struct group *g;
	g = getgrnam(groupName);
    if (g == NULL) {
        errExit("groupIdFromName");
    }
    return &(g->gr_gid);
}

uid_t* userIdFromName(char* userName)
{
	struct passwd *p;
	p = getpwnam(userName);
    if (p == NULL) {
        errExit("userIdFromName");
    }
    return &(p->pw_uid);
}

int main(int argc, char *argv[])
{
    acl_t acl;
    acl_type_t type;
    acl_entry_t entry;
    acl_tag_t tag;
    uid_t *uidp;
    gid_t *gidp;
    acl_permset_t permset;
    char  *text_acl;
    ssize_t len;

    type = ACL_TYPE_ACCESS;

    acl = acl_get_file("test2", type);
    if (acl == NULL)
        errExit("acl_get_file");

    text_acl = acl_to_text(acl, &len);
    if (text_acl == NULL)
    {
        perror ("acl_to_text()");
        return EXIT_FAILURE;
    }
    printf ("Initial ACL:\n%s\n", text_acl);

    if(acl_create_entry(&acl, &entry) == -1)
        errExit("acl_create_entry");

    tag = ACL_USER;
    acl_set_tag_type(entry, tag);

    uidp = userIdFromName("jimmy");
    printf("uid : %d\n", *uidp);
    if(acl_set_qualifier(entry, uidp) == -1)
        errExit("acl_set_qualifier");

    if(acl_get_permset(entry, &permset) == -1)
        errExit("acl_get_permset");

    if(acl_clear_perms(permset) == -1)
        errExit("acl_clear_perms");

    if(acl_add_perm(permset, ACL_READ) == -1)
        errExit("acl_add_perm ACL_READ");

    if(acl_add_perm(permset, ACL_EXECUTE) == -1)
        errExit("acl_add_perm ACL_EXECUTE");

    acl_set_file("test2", type, acl);

    /* Create Group */

    if(acl_create_entry(&acl, &entry) == -1)
        errExit("acl_create_entry");
    
    tag = ACL_GROUP;
    acl_set_tag_type(entry, tag);

    gidp = groupIdFromName("group2");
    printf("gid : %d\n", *gidp);
    if(acl_set_qualifier(entry, gidp) == -1)
        errExit("acl_set_qualifier");

    if(acl_get_permset(entry, &permset) == -1)
        errExit("acl_get_permset");

    if(acl_clear_perms(permset) == -1)
        errExit("acl_clear_perms");

    if(acl_add_perm(permset, ACL_READ) == -1)
        errExit("acl_add_perm ACL_READ");

    if(acl_add_perm(permset, ACL_EXECUTE) == -1)
        errExit("acl_add_perm ACL_EXECUTE");

    acl_set_file("test2", type, acl);

    acl_free(acl);

	return 0;
}