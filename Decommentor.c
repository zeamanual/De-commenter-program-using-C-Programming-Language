#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum State{
    NORMAL_CODE,
    TO_COMMENT,
    SINGLE_LINE_COMMENT,
    MULTIPLE_LINE_COMMENT,
    TO_END_COMMENT,
    UNTERMINTATED_COMMENT,
    DOUBLEQUOTE,
    SINGLEQUOTE
};

enum State handle_normalcode_state(char character,char *uncommented){
    enum State state = NORMAL_CODE;
    int single_quote_ascii=39;
    if(character=='/'){
        state=TO_COMMENT;
    }else if(character=='"'){
        strncat(uncommented,&character,1);
        state=DOUBLEQUOTE;
    }else if(character=='\''){
        strncat(uncommented,&character,1);
        state=SINGLEQUOTE;
    }else if(character==EOF){
        state = NORMAL_CODE;
    }else{
        strncat(uncommented,&character,1);
    }
    return state;
}
enum State handle_to_comment_state(char character,char *uncommented,int current_line_number,int *comment_start_line){
    enum State state = SINGLE_LINE_COMMENT;
    if(character=='*'){
        char space=' ';
        *comment_start_line=current_line_number;
        state=SINGLE_LINE_COMMENT;
        strncat(uncommented,&space,1);
    }else if(character=='/'){
        char forwar_slash='/';
        strncat(uncommented,&forwar_slash,1);
        state=TO_COMMENT;
    }else{
        state=NORMAL_CODE;
        char forwar_slash='/';
        strncat(uncommented,&forwar_slash,1);
        strncat(uncommented,&character,1);
    }
    return state;
}

// For handling a comment without a new line character
enum State handle_single_line_comment_state(char character, char *uncommented){
    enum State state = SINGLE_LINE_COMMENT;
    if(character=='*'){
        state=TO_END_COMMENT;
    }else if(character=='\n'){
        char new_line = '\n';
        state=MULTIPLE_LINE_COMMENT;
        strncat(uncommented,&new_line,1);
    }else if(character==EOF){
        state=UNTERMINTATED_COMMENT;
    }
    return state;
}

// For hadling a comment with a new line character
enum State handle_multi_line_comment_state(char character, char *uncommented){
    enum State state = MULTIPLE_LINE_COMMENT;
    if(character=='*'){
        state=TO_END_COMMENT;
    }else if(character=='\n'){
        char new_line = '\n';
        strncat(uncommented,&new_line,1);
    }else if(character==EOF){
        state=UNTERMINTATED_COMMENT;
    }
    return state;
}
enum State handle_singlequote_state(char character,char *uncommented){
    enum State state = SINGLEQUOTE;
    if(character=='\''){
        state=NORMAL_CODE;
    }else if(character==EOF){
        state=SINGLEQUOTE;
        return state;
    }
    strncat(uncommented,&character,1);
    return state;
}
enum State handle_doublequote_state(char character,char *uncommented){
    enum State state = SINGLEQUOTE;
    if(character=='"'){
        state=NORMAL_CODE;
    }else if(character==EOF){
        state=DOUBLEQUOTE;
        return state;
    }
    strncat(uncommented,&character,1);
    return state;
}
enum State handle_to_end_comment_state(char character){
    enum State state = SINGLE_LINE_COMMENT;
    if(character=='/'){
        state=NORMAL_CODE;
    }else if(character=='*'){
        state=TO_END_COMMENT;
    }else if(character==EOF){
        state=UNTERMINTATED_COMMENT;
    }
    return state;
}



int main(int nArgs, char *Args[]){
    
    return 0;
}