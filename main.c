#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>

#define SPEC_SYMBOL "-$/~\\"
#define BRACKETS "(){}\'\'\"\""


//libmx



typedef struct s_list {
    void *data;
    struct s_list *next;
} t_list;

int mx_atoi(const char *str);
int mx_binary_search(char **arr, int size, const char *s, int *count);
int mx_bubble_sort(char **arr, int size);
int mx_count_substr(const char *str, const char *sub);
int mx_count_words(const char *str, char delimiter);
int mx_count_words_space(const char *str);
t_list *mx_create_node(void *data);
char *mx_del_extra_spaces(const char *str);
void mx_del_strarr(char ***arr);
char *mx_file_to_str(const char *file);
void mx_foreach(int *arr, int size, void (*f)(int));
int mx_get_char_index(const char *str, char c);
int mx_get_substr_index(const char *str, const char *sub);
unsigned long mx_hex_to_nbr(const char *hex);
bool mx_isdigit(int c);
bool mx_islower(int c);
bool mx_isspace(char c);
bool mx_isupper(int c);
char *mx_itoa(int number);
int mx_linear_search(char **arr, const char *s);
int mx_list_size(t_list *list);
void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n);
void *mx_memchr(const void *s, int c, size_t n);
int mx_memcmp(const void *s1, const void *s2, size_t n);
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n);
void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len);
void *mx_memmove(void *dst, const void *src, size_t len);
void *mx_memset(void *b, int c, size_t len);
char *mx_nbr_to_hex(unsigned long nbr);
void mx_pop_back(t_list **head);
void mx_pop_front(t_list **head);
void mx_pop_index(t_list **list, int index);
double mx_pow(double n, unsigned int pow);
void mx_print_error(const char *str, int exit_code);
void mx_print_strarr(char **arr, const char *delim);
void mx_printchar(char c);
void mx_printint(int n);
void mx_printstr(const char *s);
void mx_push_back(t_list **list, void *data);
void mx_push_front(t_list **list, void *data);
void mx_push_index(t_list **list, void *data, int index);
char *mx_replace_substr(const char *str, const char *sub, const char *replace);
t_list *mx_sort_list(t_list *list, bool (*cmp)(void *, void *));
int mx_sqrt(int x);
void mx_str_reverse(char *s);
char *mx_strcat(char *restrict s1, const char *restrict s2);
char *mx_strchr(const char *s, int c);
int mx_strcmp(const char *s1, const char *s2);
char *mx_strcpy(char *dst, const char *src);
void mx_strdel(char **str);
char *mx_strdup(const char *str);
char *mx_strjoin(char const *s1, char const *s2);
int mx_strlen(const char *s);
int mx_strncmp(const char *s1, const char *s2, int n);
char *mx_strncpy(char *dst, const char *src, int len);
char *mx_strndup(const char *s1, size_t n);
char *mx_strnew(const int size);
char **mx_strsplit(const char *s, char c);
char *mx_strstr(const char *haystack, const char *needle);
char *mx_strtrim(const char *str);
char *mx_strtrim_char(const char *str, char c);
int mx_super_atoi(const char *str);
void mx_swap_char(char *s1, char *s2);
void mx_swap_str(char **s1, char **s2);
int mx_tolower(int c);
int mx_toupper(int c);



#define NO_PIPELINE 0
#define RIGHT_PIPELINE 1
#define LIGHT_PIPELINE 2
#define RIGHT_LIGHT_PIPELINE 3

#define MY_COM ""

typedef struct s_sh_str {
    char *name;
    char type;
} t_sh_str;

typedef struct s_sh_str_list {
    char *name;
    char type;
    struct s_sh_str_list *next;
} t_sh_str_list;

typedef struct s_sh_operand {
    char *name;
    char **params;
    char type; 
    int pipeline_type;
} t_sh_operand;

typedef struct s_sh_queue {
    t_sh_operand *oper1;
    t_sh_operand *oper2;
    char *act;
} t_sh_queue;

typedef struct s_main_sh {
    char **path;
    char **alias;
    char **env;
    char **my_com;
    t_sh_queue *queue;
    char *input_str;
    t_sh_str **pstr;
    t_sh_str_list *lstr;
    int pstr_len;
    char **history;
} t_main_sh;

bool mx_check_symbol(char s) {
    if (s >= 'a' && s <= 'z')
        return true;
    else if (s >= 'A' && s <= 'Z')
        return true;
    else if (s >= '0' && s <= '9')
        return true;
    else if (s == '/')
        return true;
    else if (s == '.')
        return true;
    return false;
}

bool mx_check_bracket(char s) {
    switch (s) {
        case '(': return true; break;
        case ')': return true; break;
        case '{': return true; break;
        case '}': return true; break;
        case '\'': return true; break;
        case '$': return true; break;
        case '\"': return true; break;
        case '`': return true; break;
        default: return false; break;
    }
}

bool mx_check_spec_symbol(char s) {
    switch (s) {
        //case '/': return true; break;
        case '-': return true; break;
        case '\\': return true; break;
        case '~': return true; break;
        case '#': return true; break;
        case '?': return true; break;
        default: return false; break;
    }
}

bool mx_check_command(char s) {
    switch(s) {
        case '&': return true; break;
        case '|': return true; break;
        case ';': return true; break;
        case '<': return true; break;
        case '>': return true; break;
        default: return false; break;
    }
}

t_sh_str_list *mx_sh_str_list_create(char *s, char type) {
    t_sh_str_list *tmp = malloc(sizeof(t_sh_str_list));

    tmp->name = s;
    tmp->type = type;
    tmp->next = NULL;
    return tmp;
}

int mx_command_len(char *s) {
    int len = 1;

    for (int i = 1; s[i]; i++) {
        if (mx_check_symbol(s[i]))
            len++;
        else
            break;
    }
    return len;
}

void mx_str_sh_add(t_sh_str_list **pstr, char *s, char type, int len) {
    t_sh_str_list *temp = *pstr;
    char *str = mx_strndup(s, len);

    if (!temp)
        *pstr = mx_sh_str_list_create(str, type);
    else {
        while (temp->next)
            temp = temp->next;
        temp->next = mx_sh_str_list_create(str, type);
    }
}


t_sh_str_list *mx_parse_input_str(char *str) {
    t_sh_str_list *pstr = NULL;
    int len = 0;
    int bracket_round = 0;
    int bracket_curly = 0;

    for (int i = 0; str[i]; i++) {
        if (mx_check_command(str[i]) && mx_check_command(str[i+1])) {
            mx_str_sh_add(&pstr, &str[i], 'k', 2); 
            i += 1;
        }
        else if (mx_check_command(str[i])) {
            mx_str_sh_add(&pstr, &str[i], 'k', 1); 
        }
        else if (mx_check_symbol(str[i])) {
            len = mx_command_len(&str[i]);
            mx_str_sh_add(&pstr, &str[i], 'c', len);
            i += len - 1;
        }
        else if (mx_check_spec_symbol(str[i]))
            mx_str_sh_add(&pstr, &str[i], 's', 1); 
        else if (mx_check_bracket(str[i])) {
            if (str[i] == '$' && str[i+1] == '(') {
                mx_str_sh_add(&pstr, &str[i], 'b', 2);
                i++;
            }
            else if (str[i] == '$' && str[i+1] == '{') {
                mx_str_sh_add(&pstr, &str[i], 'b', 2);
                i++;                
            }
            else if (str[i] == ')' && !bracket_round)
                mx_str_sh_add(&pstr, "$)", 'b', 2);
            else if (str[i] == '(') {
                mx_str_sh_add(&pstr, "(", 'b', 1); 
                bracket_round += 1;
            }
            else if (str[i] == ')' && bracket_round) {
                mx_str_sh_add(&pstr, ")", 'b', 1);
                bracket_round -= 1;
            }
            else if (str[i] == '}' && bracket_curly) {
                mx_str_sh_add(&pstr, "}", 'b', 1);
                bracket_curly -= 1;
            }  
            else if (str[i] == '{') {
                mx_str_sh_add(&pstr, "{", 'b', 1); 
                bracket_curly += 1;
            } 
            else if (str[i] == '}' && !bracket_curly)
                mx_str_sh_add(&pstr, "$}", 'b', 2);
            else if (str[i] == '\"')
                mx_str_sh_add(&pstr, "\"", 'b', 1); 
            else if (str[i] == '\'')
                mx_str_sh_add(&pstr, "\'", 'b', 1);       
            else
                mx_str_sh_add(&pstr, "$", 'b', 1); 
        }
    }
    return pstr;
}

void mx_print_str_sh(t_sh_str_list *pstr) {
    t_sh_str_list *tmp = pstr;

    if (!tmp)
        mx_printstr("null");
    else
        while(tmp) {
            mx_printstr("Elem:");
            mx_printchar(' ');
            mx_printstr(tmp->name);
            mx_printchar(' ');
            mx_printchar(tmp->type);
            mx_printchar('\n');
            tmp = tmp->next;
        }
}

void mx_get_sh_str_len(t_main_sh *main) {
    int len = 0;
    t_sh_str_list *tmp = main->lstr;

    
    if (tmp)
        while(tmp) {
            tmp = tmp->next;
            len++;
        }
    main->pstr_len = len;
}

t_sh_str **mx_sh_str_create(int len) {
    t_sh_str **pstr = (t_sh_str**)malloc(sizeof(t_sh_str*) * len);

    for (int i = 0; i <= len; i++)
        pstr[i] = NULL;
    return pstr;
}

void mx_get_sh_pstr(t_main_sh *main) {
    t_sh_str **pstr = mx_sh_str_create(main->pstr_len + 1);
    t_sh_str_list *tmp = main->lstr;

    for (int i = 0; tmp; tmp = tmp->next, i++) {
        pstr[i] = (t_sh_str*)malloc(sizeof(t_sh_str));
        pstr[i]->name = tmp->name;
        pstr[i]->type = tmp->type;
    }
    main->pstr = pstr;
}

t_sh_str *mx_copy_sh_str(t_sh_str *pstr) {
    t_sh_str *copy = (t_sh_str*)malloc(sizeof(t_sh_str));

    copy->name = mx_strdup(pstr->name);
    copy->type = pstr->type;
    return copy;
}



bool mx_check_one_command(t_sh_str *pstr) {
    if (pstr->type == 'b')
        return true;
    else
        return false;
}

t_sh_queue *mx_create_queue(t_sh_operand *oper1, t_sh_operand *oper2, char *act) {
    t_sh_queue *queue = (t_sh_queue*)malloc(sizeof(t_sh_queue));

    queue->oper1 = oper1;
    queue->oper2 = oper2;
    queue->act = act;
    return queue;
}

char mx_get_operand_type(t_main_sh *main, char *name) {
    struct stat buf;
    stat (name, &buf);

    if (mx_get_substr_index(MY_COM, name) >= 0)
        return 'm';
    else if (S_IXUSR == (S_IXUSR & buf.st_mode))
        return 'x';
    else if (buf.st_mode > 0)
        return 'f';
    else 
        return 's';
}


int mx_get_pipeline_type(char *name) {
    return NO_PIPELINE;
}


t_sh_operand *mx_get_operand(t_main_sh *main, char *str) {
    t_sh_operand *oper = (t_sh_operand*)malloc(sizeof(t_sh_operand));
    char **param = mx_strsplit(str, ' ');

    if (param && param[0]) {
        oper->name = param[0];
        if (param[1])
            oper->params = &param[1];
        else
            oper->params = NULL;
    }
    else {
        oper->name = NULL;
        oper->params = NULL;
    }
    oper->type = mx_get_operand_type(main, oper->name);
    oper->pipeline_type = mx_get_pipeline_type(oper->name);
    return oper;
}


// void mx_add_queue(t_main_sh *main, char *str1, char *str2, char *act) {
//     t_sh_queue *tmp = main->queue;
//     t_sh_operand *oper1 = mx_get_operand(main, str1);
//     t_sh_operand *oper2 = mx_get_operand(main, str2);

//     if (!tmp)
//         main->queue = mx_create_queue(oper1, oper2, act);
//     else {
//         while(tmp->next) 
//             tmp = tmp->next;
//         tmp->next = mx_create_queue(oper1, oper2, act);
//     }
// }

void mx_del_sh_str(t_sh_str **pstr) {
    //mx_strdel(pstr->name);
    free(*pstr);
    *pstr = NULL;
}

t_sh_str *mx_queue_execve_unare(t_main_sh *main, int ind) {
    char *com = mx_strdup(main->pstr[ind]->name);

    if (!mx_strcmp(com, "\"") || !mx_strcmp(com, "\'")) {
        
    }
}

t_sh_str *mx_queue_execve_binary(t_main_sh *main, int index) {
    if (main)
        index++;
    return NULL;
}

void mx_sh_treat_brackets(t_main_sh *main) {
    int j = 0;
    t_sh_str *tmp = NULL;

    for (int i = 0; main->pstr[i]; i++) {
        if (main->pstr[i]->type == 'b' && main->pstr[i+1] && main->pstr[i+2]
            && !mx_strcmp(main->pstr[i]->name, main->pstr[i+2]->name)) {
                main->pstr[i]->type = '=';
                main->pstr[i+2]->type = '=';
                tmp = mx_copy_sh_str(main->pstr[i+1]);
                mx_del_sh_str(&main->pstr[i+1]);
                main->pstr[i+1] = mx_queue_execve_unare(main, i);
                mx_del_sh_str(&tmp);
        }
    }
}

int mx_get_end_params_index(t_sh_str **pstr, int begin) {
    int end = begin;

    while(pstr[end] && pstr[end]->type == 'c')
        end++;
    return end - 1;
}


void mx_queue_hyphenation_params(t_sh_str **pstr, int begin, int end) {
    char *tmp = NULL;

    for (int i = begin + 1; i <= end; i++) {

        tmp = mx_strdup(pstr[begin]->name);
        //mx_strdel(&pstr[begin]->name);
        pstr[begin]->name = mx_strjoin(pstr[begin]->name, " ");
        pstr[begin]->name = mx_strjoin(pstr[begin]->name, pstr[i]->name);
        //mx_strdel(&pstr[i]->name);
        pstr[i]->type = '=';
        //mx_strdel(&tmp);
    }
}

void mx_sh_treat_params(t_main_sh *main) {
    int i = 0;
    int end = 0;

    while (main->pstr[i] != NULL) {
        if (main->pstr[i]->type == 'c') {
            end = mx_get_end_params_index(main->pstr, i);
            mx_queue_hyphenation_params(main->pstr, i, end);
        }
        i++;
    }
}

void mx_sh_treat_commands(t_main_sh *main) {
    int j = 0;
    t_sh_str *tmp = NULL;

    for (int i = 0; main->pstr[i]; i++)
        if (main->pstr[i]->type == 'c' && main->pstr[i+1] && main->pstr[i+2] 
            && main->pstr[i+2]->type == 'c' && main->pstr[i+1]->type == 'k') {
                main->pstr[i+1]->type = '=';
                main->pstr[i+2]->type = '=';
                tmp = mx_copy_sh_str(main->pstr[i]);
                mx_del_sh_str(&main->pstr[i]);
                main->pstr[i] = mx_queue_execve_binary(main, i);
                mx_del_sh_str(&tmp);      
        }
}

// int mx_get_pstr_clear_len(t_sh_str **pstr) {
//     int len = 0;

//     for (int i = 0; pstr[i]; i++)
//         if (pstr[i]->type != '=')
//             len++;
//     return len;
// }

void mx_sh_str_clear(t_main_sh *main) {
    char *tmp_name = NULL;
    char tmp_type;
    int j = 0;

    for (int i = 0; main->pstr[i]; i++)
        if (main->pstr[i]->type != '=') {
            tmp_name = mx_strdup(main->pstr[i]->name);
            tmp_type = main->pstr[i]->type;
            mx_strdel(&main->pstr[j]->name);
            main->pstr[j]->name = mx_strdup(tmp_name);
            main->pstr[j]->type = tmp_type;
            mx_strdel(&tmp_name);
            j++;
        }
    for (int i = j; i < main->pstr_len; i++)
        mx_del_sh_str(&main->pstr[i]);
    main->pstr_len = j;
}

int mx_sh_get_pstr_len(t_main_sh *main) {
    int len = 0;

    for (int i = 0; main->pstr[i]; i++)
        len++;
    return len;
}

void mx_print_queue(t_main_sh *main) {
    for (int i = 0; main->pstr[i]; i++) {
        mx_printstr(main->pstr[i]->name);
        mx_printchar(' ');
    }
    mx_printchar('\n');
    for (int i = 0; main->pstr[i]; i++) {
        mx_printchar(main->pstr[i]->type);
        for (int j = 0; j < mx_strlen(main->pstr[i]->name); j++)
            mx_printchar(' ');
    }
    mx_printchar('\n');  
}

//work
void mx_execve_pstr(t_main_sh *main) {
    int count = 0;
    int pstr_len = 0;

    while (1) {
        mx_sh_treat_params(main);
        //mx_print_queue(main);
        mx_sh_str_clear(main);
        //mx_print_queue(main);
        mx_sh_treat_brackets(main);
        mx_print_queue(main);
        mx_sh_str_clear(main);
        mx_sh_treat_params(main);
        mx_sh_str_clear(main);
        mx_sh_treat_commands(main);
        mx_sh_str_clear(main); 
        pstr_len = mx_sh_get_pstr_len(main);
        if (pstr_len == 1)
            break;
        count++;
        if (count >= main->pstr_len)
            break;
    }
}

t_main_sh *mx_create_main_sh(char *str, char **env) {
    t_main_sh *main = (t_main_sh*)malloc(sizeof(t_main_sh));
    char *path = NULL;

    for (int i = 0; env[i]; i++)
        if (mx_get_substr_index(env[i], "PATH=") >= 0) {
            path = mx_strdup(&env[i][6]);
            break;
        }
    main->input_str = str;
    main->pstr = NULL;
    main->lstr = NULL;
    main->queue = NULL;
    main->my_com = mx_strsplit(MY_COM, ':');
    main->env = env;
    main->alias = NULL;
    main->path = mx_strsplit(path, ':');
    main->pstr_len = 0;
    main->history = NULL;
    mx_strdel(&path);
    return main;
}

void mx_loop(char **env) {
    char *str = NULL;
    int len = 0;
    t_main_sh *main = NULL;

    str = mx_strdup("ls \"main test\"");
    main = mx_create_main_sh(str, env);
    main->lstr = mx_parse_input_str(str);
    //mx_print_str_sh(main->lstr);
    mx_get_sh_str_len(main);
    mx_get_sh_pstr(main);
    mx_execve_pstr(main);
}


int main (int argc, char **argv, char **env) {
    mx_loop(env);

    return 0;
}
