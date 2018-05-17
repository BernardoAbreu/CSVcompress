#include <stdio.h>
#include <stdlib.h>

char convert(char c){
    if(c >= 0x30 && c < 0x40){
        return c - 0x30;
    }

    switch(c){
        case '.':
            return (char)10;
        case '\n':
            return (char)11;
        case '+':
            return (char)12;
        case '-':
            return (char)13;
        case ' ':
            return (char)14;
        case '$':
            return (char)15;
    }
}

char deconvert(char c){
    if(c < 10){
        return c + 0x30;
    }
    // printf("%d\n", (int)c);

    switch(c){
        case 10:
            return '.';
        case 11:
            return '\n';
        case 12:
            return '+';
        case 13:
            return '-';
        case 14:
            return ' ';
        case 15:
            return '$';
    }
}



char compress(char n1, char n2){
    n1 = convert(n1);
    n2 = convert(n2);

    return n1 << 4 | (n2 & 0x0F);

}


void compress_file2(char* input_file, char* output_file){
    FILE *fp_in, *fp_out;
    int num1, num2, last;

    if ((fp_in = fopen(input_file, "r")) == NULL){
       printf("Error! opening file");
       exit(1);
    }

    if((fp_out = fopen(output_file, "w")) == NULL){
        printf("Error creating output file!");
        exit(1);             
    }

    int end = 0;
    // fputc(1, fp_out);

    while(!end){ 
        num1 = fgetc(fp_in);
        if(num1 == EOF){
            break;
        }
        if((char)num1 == 'e'){
            num1 = fgetc(fp_in);
        }

        num2 = fgetc(fp_in);

        if(num2 == EOF){
            num2 = '$';
            end = 1;
        }

        if((char)num2 == 'e'){
            num2 = fgetc(fp_in);
        }

        //process ch

        fputc(compress((char)num1, (char)num2), fp_out);
    }
    // if(end){
    //     fseek(fp_out, 0, SEEK_SET);
    //     fputc(2, fp_out);
    // }

    fclose(fp_in);
    fclose(fp_out);
}

void compress_file(){
    int end = 0;

    while(!end){ 
        num1 = fgetc(fp_in);
        if(num1 == EOF){
            break;
        }
        if((char)num1 == 'e'){
            num1 = fgetc(fp_in);
        }

        num2 = fgetc(fp_in);

        if(num2 == EOF){
            num2 = '$';
            end = 1;
        }

        if((char)num2 == 'e'){
            num2 = fgetc(fp_in);
        }

        fputc(compress((char)num1, (char)num2), fp_out);
    }

}


void decompress_file2(char* input_file, char* output_file){
    FILE *fp_in, *fp_out;

    if ((fp_in = fopen(input_file, "r")) == NULL){
       printf("Error! opening file");
       exit(1);
    }

    if((fp_out = fopen(output_file, "w")) == NULL){
        printf("Error creating output file!");
        exit(1);             
    }

    int new;
    char c, last;
    last = ' ';

    while(1){ 
        new = fgetc(fp_in);

        if(new == EOF){
            break;
        }

        // printf("%c\n", last);
        c = deconvert((char)(new >> 4));
        if(c == '+' || (c == '-' && (last >= 0x30 && last < 0x40) )){
            fputc('e', fp_out);
        }
        fputc(c, fp_out);
        last = c;

        c = deconvert((char)(new & 0xF));
        if(c == '$') break;

        if(c == '+' || (c == '-' && (last >= 0x30 && last < 0x40) )){
            fputc('e', fp_out);
        }

        fputc(c, fp_out);
        last = c;
    }


    fclose(fp_in);
    fclose(fp_out);
}

void decompress_file(){

    int new;
    char c, last;
    last = ' ';

    while(1){ 
        new = getc(stdin);

        if(new == EOF){
            break;
        }

        // printf("%c\n", last);
        c = deconvert((char)(new >> 4));
        if(c == '+' || (c == '-' && (last >= 0x30 && last < 0x40) )){
            putc('e', stdout);
        }
        putc(c, stdout);
        last = c;

        c = deconvert((char)(new & 0xF));
        if(c == '$') break;

        if(c == '+' || (c == '-' && (last >= 0x30 && last < 0x40) )){
            putc('e', stdout);
        }

        putc(c, stdout);
        last = c;
    }

}

int main(){

    // char* input_file = "T_C_X_TP_t8.txt";
    // // char* input_file = "test.txt";
    // char* output_file = "out.txt";
    // char* new_file = "test2.txt";
    // compress_file2(input_file, output_file);
    // decompress_file2(output_file, new_file);
    compress_file(input_file, output_file);
    decompress_file(output_file, new_file);


    return 0;
}