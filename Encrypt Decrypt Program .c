#include<stdio.h>
#include<dirent.h>
#include<string.h>

FILE *read_file=NULL;                           // Input file pointer
FILE *write_file=NULL;                          // Output file pointer
int ch;                                         // temporary character

void directry(){                                // show file names inside the vault folder
    DIR *d;
    struct dirent *dir;
    int i=1;

    d = opendir("Vault/");
    if (d){
        printf("\n\tVault/\n");
        while ((dir = readdir(d)) != NULL){
            if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)    // to exclude 2 special system files
                continue;
            printf("\t%d. %s\n",i, dir->d_name);
            i++;
        }
        closedir(d);
    }
}

int encrypt(){
    ch = fgetc(read_file);                      // read file character by character in binary form
    while(ch != EOF)                            // until ch hit 'End of File'
    {
        ch = ch+33;                             // encrypting algorithm
        fputc(ch, write_file);                  // write to output file
        ch = fgetc(read_file);                  // read next value
    }
    return 0;
}

int decrypt(){
    ch = fgetc(read_file);                      // read  character by character
    while(ch != EOF)                            // until ch hit 'End of File'
    {
        ch = ch-33;                             // decrypting algorithm
        fputc(ch, write_file);                  // write to output file
        ch = fgetc(read_file);
    }
    return 0;
}

int error(char t){                                                          // Error types
    switch(t){
        case'1':                                                            // wrong loop input
            printf("!!Invalid Input\n");
            return 0;
        case'2':                                                            // input file does not exist
            printf("!!File Not Found\n");
            return 0;
        case'3':                                                            // a file with the same name already exist
            printf("\n!!A File already has that name. Overwrite? [y/n] :");
            scanf(" %c",&t);
            if(t=='y'||t=='Y')
                return 1;
            else
                return 0;
    }
}


int main(){

    printf("\t\t\t\t\t\tFile Encrypting Program\t\t\t\t\t\t \n\n");

    int r=1;                                            // repeat code
    while(r==1){

        if(r!=0 && r!=1){
            error('1');                                 // wrong input
            return 0;
        }

        char fname[30]="Vault/", mode;                  // default file directory => Vault/file_name.extension

        printf("\nEncrypt[E] / Decrypt[D] : ");         // read program mode
        scanf(" %c",&mode);

        if(mode!='E'&& mode!='e'&& mode!='D'&& mode!='d'){
            error('1');                                 // wrong input
            return 0;
        }

        directry();

        printf("\nEnter File Name [with extension] : ");
        scanf(" %[^\n]s",&fname[6]);                    // a name for the input file
        read_file=fopen(fname,"rb");                    // read input file in Vault folder
        if(read_file == NULL){                          // check file existence
            error('2');                                 // no file to encrypt
            return 0;
        }

        while(1){
            printf("\nOutput File Name [with extension] : ");
            scanf(" %[^\n]s",&fname[6]);                // a name for the output file
            if(fopen(fname,"rb") != NULL){              // check if there exists files with same name before overwrite
                if(error('3'))
                    break;                              // user want's to overwrite
                else
                    continue;                           // user want's to give a new name
            }
            else
                break;                                  // files with the same name does not exist
        }
        write_file=fopen(fname,"wb");                   // create output file

        switch(mode){
            case 'E':
            case 'e':
                printf("\n******* Encrypting *******\n\n");
                encrypt();
                printf("\n******* Success *******\n");
                break;
            case 'D':
            case 'd':
                printf("\n******* Decrypting *******\n\n");
                decrypt();
                printf("\n******* Success *******\n");
                break;
        }

        fclose(read_file);
        fclose(write_file);

        printf("\n\n\nRerun[1/0]? :");
        scanf("%d",&r);
        printf("\n\n");
    }
    return 0;
}
