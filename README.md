# Rrrrrrush

------------------------------ 수정된 내용 요약 ------------------------------

util.keyboard_1.c    
    malloc_for ...() 함수 파라미터 추가
    get_3_simbols.() 함수 파라미터 추가
    get_col_size..() 함수 구문 변경
 
util_keyboard_2.c
    ck_ex_ac1..()   함수 파라미터 변경

util_standard.c
    위의 함수 파라미터 수정에 따라 함수 호출시 인자 수정
    
header.h
    위의 함수 수정에 따라 헤더파일 수정
    
until_solve.c
    ft_solve_map()  함수 구문 변경 (표준입력에서 줄 길이 짧을 시 floating point exception error발생. 숫자 0으로 나누기 연산을 시도할 때 발생하여 양수일 때만 가능하게 수정
    
------------------------------ 수정된 내용 요약 ------------------------------ D + 1
util_set.c 
    ft_set_input_map()함수의 구문에서 지역변수 i의 증가연산이 마지막에 이루어지지 못해서 이후 사용된 i값이 오염됐다. 기존 증가연산을 제거하고 구문 마지막 줄을 추가하여 변수 i를 증
