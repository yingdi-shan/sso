#include<cstdio>
#include<cstdlib>
char name[80];
char password[80];
char * random_str(char *str,int size){

    for(int i=0;i<size;i++){
        int test = rand()%36;
        if(test<10)
        str[i] = test+'0';
        else
        str[i] = test-10 + 'a';
    }
    str[size]='\0';
    return str;
}

void print_http(char *ip){
  //  printf("http://%s/add_user?username=%s&pwd=%s\n",ip,random_str(name,8),random_str(password,16));
    printf("%s %s\n",random_str(name,8),random_str(password,16));
}

int main(int argc, char** argv){
	freopen("http.txt","w",stdout);
	for(int i=0;i<atoi(argv[1]);i++){
        print_http(argv[2]);
	}

	return 0;
}
