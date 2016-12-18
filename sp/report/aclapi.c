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

char* groupNameFromId(gid_t gidp)
{
    struct group *g;
    g = getgrgid(gidp);
    if (g == NULL) {
        errExit("groupNameFromId");
    }
    return g->gr_name;
}

char* userNameFromId(uid_t uidp)
{
    struct passwd *p;
    p = getpwuid(uidp);
    if (p == NULL) {
        errExit("userNameFromId");
    }
    return p->pw_name;
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
    char *name;
    int entryId, permVal, opt;
    
    /* 一般的權限 */
    type = ACL_TYPE_ACCESS;

    /* 判斷是否有輸入 flag : -d */
    while ((opt = getopt(argc, argv, "d")) != -1) {
        switch (opt) {
            /* Default 權限 */
            case 'd': type = ACL_TYPE_DEFAULT; break;
            case '?': usageError(argv[0]);
        }
    }
    
    /* 確定是否有輸入 filename */
    if (optind + 1 != argc)
        usageError(argv[0]);
    
    /* 取得檔案的 ACL */
    acl = acl_get_file(argv[optind], type);
    if (acl == NULL)
        errExit("acl_get_file");
    
    /* 走過 ACL 中的所有 entry */
    for (entryId = ACL_FIRST_ENTRY; ; entryId = ACL_NEXT_ENTRY) {
        /*
            當 entry 錯誤，回傳 -1 
            當 entry 沒有下一個時，回傳 0
        */
        if (acl_get_entry(acl, entryId, &entry) != 1)
            break;

        /* 取得當前 entry 的 tag type */
        if (acl_get_tag_type(entry, &tag) == -1)
            errExit("acl_get_tag_type");
        printf("%-12s", (tag == ACL_USER_OBJ) ?  "user_obj" :
                        (tag == ACL_USER) ?      "user" :
                        (tag == ACL_GROUP_OBJ) ? "group_obj" :
                        (tag == ACL_GROUP) ?     "group" :
                        (tag == ACL_MASK) ?      "mask" :
                        (tag == ACL_OTHER) ?     "other" : "???");
        
        /* 得當前 entry 的 tag qualifier，UID、GID */
        if (tag == ACL_USER) {
            
            /* User ID */
            uidp = acl_get_qualifier(entry);
            if (uidp == NULL)
                errExit("acl_get_qualifier");
            
            name = userNameFromId(*uidp);
            
            if (name == NULL)
                printf("%-8d ", *uidp);
            else
                printf("%-8s ", name);
            if (acl_free(uidp) == -1)
                errExit("acl_free");
        } else if (tag == ACL_GROUP) {
            
            /* Group ID */
            gidp = acl_get_qualifier(entry);
            if (gidp == NULL)
                errExit("acl_get_qualifier");
            
            name = groupNameFromId(*gidp);
            
            if (name == NULL)
                printf("%-8d ", *gidp);
            else
                printf("%-8s ", name);
            if (acl_free(gidp) == -1)
                errExit("acl_free");
        } else {
            printf("         ");
        }
        
        /* 得當前 entry 的 permissions */
        if (acl_get_permset(entry, &permset) == -1)
            errExit("acl_get_permset");
        
        /* Read 權限 */
        permVal = acl_get_perm(permset, ACL_READ);
        if (permVal == -1)
            errExit("acl_get_perm - ACL_READ");
        printf("%c", (permVal == 1) ? 'r' : '-');
                
        /* Write 權限 */
        permVal = acl_get_perm(permset, ACL_WRITE);
        if (permVal == -1)
            errExit("acl_get_perm - ACL_WRITE");
        printf("%c", (permVal == 1) ? 'w' : '-');
        
        /* Execute 權限 */
        permVal = acl_get_perm(permset, ACL_EXECUTE);
        if (permVal == -1)
            errExit("acl_get_perm - ACL_EXECUTE");
        printf("%c", (permVal == 1) ? 'x' : '-');
        printf("\n");
    }
    
    /*  */
    if (acl_free(acl) == -1)
        errExit("acl_free");
    exit(EXIT_SUCCESS);

    return 0;
}