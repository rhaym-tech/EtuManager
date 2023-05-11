#define MAX_STUDENTS 100
#define MAX_NAME_LEN 50
#define MAX_ADDRESS_LEN 100
#define MAX_EMAIL_LEN 50
#define MAX_MODULES 10


typedef struct {
    char nom_module[MAX_NAME_LEN];
    float coefficient;
    float note;
} module;

typedef struct {
    long long int id;
    char nom[MAX_NAME_LEN];
    char prenom[MAX_NAME_LEN];
    char adresse[MAX_ADDRESS_LEN];
    char email[MAX_EMAIL_LEN];
    int age;
    float moyenne;
    module modules[MAX_MODULES];
    int nb_modules;
} student;