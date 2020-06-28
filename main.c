#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
} t_sh_operand;

typedef struct s_sh_queue {
    t_sh_operand *opr1;
    t_sh_operand *opr2;
    char *act;
    struct s_sh_queue *next;
} t_sh_queue;

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

int mx_get_sh_str_len(t_sh_str_list *lstr) {
    int len = 0;
    t_sh_str_list *tmp = lstr;

    
    if (tmp)
        while(tmp) {
            tmp = tmp->next;
            len++;
        }
    return len;
}

t_sh_str **mx_sh_str_create(int len) {
    t_sh_str **pstr = (t_sh_str**)malloc(sizeof(t_sh_str*) * len);

    for (int i = 0; i <= len; i++)
        pstr[i] = NULL;
    return pstr;
}

t_sh_str **mx_get_sh_pstr(t_sh_str_list *lstr, int len) {
    t_sh_str **pstr = mx_sh_str_create(len);
    t_sh_str_list *tmp = lstr;

    for (int i = 0; tmp; tmp = tmp->next, i++) {
        pstr[i] = (t_sh_str*)malloc(sizeof(t_sh_str));
        pstr[i]->name = tmp->name;
        pstr[i]->type = tmp->type;
    }
    return pstr;
}

t_sh_str **mx_copy_sh_str(t_sh_str **pstr, len) {
    t_sh_str **copy = mx_sh_str_create(len);

    for (int i = 0; pstr[i]; i++) {
        copy[i] = (t_sh_str)malloc(sizeof(t_sh_str));
        copy[i]->name = pstr[i]->name;
        copy[i]->type = pstr[i]->type;
    }
    return copy;
}

bool mx_check_one_command(t_sh_str *pstr) {
    if (pstr[i]->type = 'b')
        return true;
    else
        return false;
}

void mx_add_queue(char *oper1, char *oper2, char *act) {

}

t_sh_queue *mx_create_queue_arr(t_sh_str **pstr, int len) {
    t_sh_queue *queue = NULL;
    t_sh_str **pstr_copy = mx_copy_sh_str(pstr, len);
    int i = 0;
    int count = 0;

    if (pstr) {
        while (1) {
            i = 0;
            while (pstr[i]) {
                if (mx_check_one_command(pstr[i])) {
                    if (mx_strcmp(pstr[i]->name, "$")) {
                        mx_add_queue();
                    }

                }
            }
            count++;
            if (count >= len)
                break;
        }
    }
    return queue;
}

void mx_loop() {
    char *str = NULL;
    t_sh_str_list *lstr = NULL;
    t_sh_str **pstr = NULL;
    int len = 0;
    t_sh_queue *queue = NULL;

    str = mx_strdup("ls /dev/null");
    lstr = mx_parse_input_str(str);
    //mx_print_str_sh(lstr);
    len = mx_get_sh_str_len(lstr);
    pstr = mx_get_sh_pstr(lstr, len);
    queue = mx_create_queue_arr(pstr, len);

}


int main (int argc, char **argv) {
    mx_loop();

    return 0;
}
