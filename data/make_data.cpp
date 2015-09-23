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
    printf("http://%s/add_user?name=%s&pwd=%s\n",ip,random_str(name,8),random_str(password,16));
}

int main(){
	freopen("http.txt","w",stdout);
	for(int i=0;i<10000000;i++){
        print_http("127.0.0.1:80");
	}

	return 0;
}
