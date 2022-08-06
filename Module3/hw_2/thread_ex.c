/* Программа 06-2.c для иллюстрации работы двух нитей исполнения.
Каждая нить исполнения просто увеличивает на 1 разделяемую 
переменную a. */ 
#include <pthread.h>
#include <stdio.h>
int a = 0; 
/* Переменная a является глобальной статической для всей 
программы, поэтому она будет разделяться обеими нитями 
исполнения.*/
/* Ниже следует текст функции, которая будет 
ассоциирована со 2-м thread'ом */
void *mythread(void *dummy)
/* Параметр dummy в нашей функции не используется и 
присутствует только для совместимости типов данных. По той
же причине функция возвращает значение void *, хотя
это никак не используется в программе.*/
{
    pthread_t mythid; /* Для идентификатора нити исполнения */
    /* Заметим, что переменная mythid является 
динамической локальной переменной функции mythread(), 
т. е. помещается в стеке и, следовательно, не разделяется
нитями исполнения. */
    /* Запрашиваем идентификатор thread'а */
    mythid = pthread_self();
    a = a+1;
    printf("Thread %d, Calculation result = %d\n", 
        mythid, a);
    return NULL;
}
/* Функция main() – она же ассоциированная функция главного
thread'а */
int main()
{
    pthread_t thid, mythid;
    int result;
    /* Пытаемся создать новую нить исполнения, 
ассоциированную с функцией mythread(). Передаем ей 
в качестве параметра значение NULL. В случае удачи в 
переменную thid занесется идентификатор нового thread'а.
Если возникнет ошибка, то прекратим работу. */
    result = pthread_create( &thid, 
        (pthread_attr_t *)NULL, mythread, NULL);
    if(result != 0){
    printf ("Error on thread create, return value = %d\n", result);
    exit(-1);
    }
    printf("Thread created, thid = %d\n", thid);
    /* Запрашиваем идентификатор главного thread'а */
    mythid = pthread_self();
    a = a+1; 
    printf("Thread %d, Calculation result = %d\n", 
        mythid, a);
    /* Ожидаем завершения порожденного thread'a, не 
    интересуясь, какое значение он нам вернет. Если не 
    выполнить вызов этой функции, то возможна ситуация, 
    когда мы завершим функцию main() до того, как выполнится 
    порожденный thread, что автоматически повлечет за 
    собой его завершение, исказив результаты. */
    pthread_join(thid, (void **)NULL);
    return 0;
}