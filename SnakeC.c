#include<graphics.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<dos.h>
 
#define UP_KEY 'H'
#define RIGHT_KEY 'M'
#define DOWN_KEY 'P'
#define LEFT_KEY 'K'
 
#define UP_DIRECTION 3
#define RIGHT_DIRECTION 1
#define DOWN_DIRECTION 4
#define LEFT_DIRECTION 2
 
#define True 1
#define False 0
 
typedef struct node
{
    int x,y,radius;
    struct node *next;
}node;
 
typedef struct queue
{
    node *rear,*front;
}queue;
 
void init(queue *t)
{
    t->rear=t->front=NULL;
}
 
int empty(queue *t)
{
    if(t->rear==NULL)
        return 0;
    return 1;
}
 
void insert(queue *t,int x1,int y1,int r1)
{
    node *p;
    p=(node*)malloc(sizeof(node));
    p->x=x1;
    p->y=y1;
    p->radius=r1;
    p->next=NULL;
 
    if(t->rear==NULL)
    {
        t->front=t->rear=p;
    }
    else
    {
        (t->rear)->next=p;
        t->rear=p;
    }
}
 
int delete(queue *t)
{
    int x;
    node *u;
    u=t->front;
 
    if(t->rear==t->front)
    {
        init(t);
    }
    else
    {
        t->front=(t->front)->next;
    }
    free(u);
    return x;
 }
 
void display_snake(queue *t)
{
    node *s;
    s=t->front;
    while(s!=NULL)
    {
        circle(s->x,s->y,s->radius);
        s=s->next;
    }
}
 
void init_snake(queue *t)
{
    insert(t,6,204,3);
    insert(t,12,204,3);
    insert(t,18,204,3);
    insert(t,24,204,3);
    insert(t,30,204,3);
    // so now next node will be insert(t,36,204,3)
    // check variable snake_head_x_cord and snake_head_y_cord
    // in main function
}
 
void main()
{
    queue p,*t=&p;
    node *s;
    int snake_head_x_cord=36,snake_head_y_cord=204,dir=RIGHT_DIRECTION,draw_food=True,i,score=0,food_x_cord,food_y_cord,gdriver = DETECT, gmode;
    char key_pressed;
    initgraph(&gdriver, &gmode, "..\\bgi");
    init(t);
    init_snake(t);
    printf("\n\n\n\n\n\n\t\tUse Arrow Keys To Controll Snake\n\t\t\tPress 'q' to Quit\n\t\t\tPress Enter to Play");
    getch();
    cleardevice();
    display_snake(t);
    rectangle(1,7,485,455);
    rectangle(3,9,483,453);
    gotoxy(65,10);
    printf("score:%d",score);
 
    // Loop forever until snake collide with walls or himself
    while(True)
    {
	if(draw_food==True)
	{
	    // find co-ordinates for food
	    while(True)
	    {
		food_x_cord=random(480);
		food_y_cord=random(450);
 
                // new food generated should have correct x and y co-ordinate, so
                // that it will match with x&y co-ordinates of head of snake to occur
                // collision
                if(food_x_cord%6==0&&food_y_cord%6==0&&food_x_cord>5&&food_y_cord>11)
                    break;
            }
        }
        // draw food
        circle(food_x_cord,food_y_cord,3);
        draw_food=False;
 
        // if snake collide with food
        if((t->rear)->x==food_x_cord&&(t->rear)->y==food_y_cord)
        {
            score++;
            draw_food=True;
            sound(11000);
            delay(20);
            nosound();
 
            // increase length of snake by 1,
            // i.e. add new node in front of head node
            if(dir==RIGHT_DIRECTION)
                insert(t,snake_head_x_cord+4,snake_head_y_cord,5);
            if(dir==LEFT_DIRECTION)
                insert(t,snake_head_x_cord-4,snake_head_y_cord,5);
            if(dir==UP_DIRECTION)
                insert(t,snake_head_x_cord,snake_head_y_cord-4,5);
            if(dir==4)
                insert(t,snake_head_x_cord,snake_head_y_cord+4,5);
 
        }
 
        // read key pressed by user
        if(kbhit())
        {
            key_pressed=getch();
            if(key_pressed=='q')
                exit(0);
            key_pressed=getch();
        }
 
        // set the direction of snake
        if(key_pressed==LEFT_KEY&&dir!=RIGHT_DIRECTION)
            dir=LEFT_DIRECTION;
        if(key_pressed==RIGHT_KEY&&dir!=LEFT_DIRECTION)
            dir=RIGHT_DIRECTION;
        if(key_pressed==UP_KEY&&dir!=DOWN_DIRECTION)
            dir=UP_DIRECTION;
        if(key_pressed==DOWN_KEY&&dir!=UP_DIRECTION)
            dir=DOWN_DIRECTION;
 
        // turn and move snake according to key pressed by user
        if(dir==RIGHT_DIRECTION)
        {
            snake_head_x_cord=snake_head_x_cord+6;
            display_snake(t);
            circle(food_x_cord,food_y_cord,3);
            // Delete node from tail
            delete(t);
            // insert node next to head
            insert(t,snake_head_x_cord,snake_head_y_cord,3);
            rectangle(1,7,485,455);
            rectangle(3,9,483,453);
            gotoxy(65,10);
            printf("score:%d",score);
            delay(50);
            cleardevice();
        }
 
        if(dir==LEFT_DIRECTION)
        {
            snake_head_x_cord=snake_head_x_cord-6;
            display_snake(t);
            circle(food_x_cord,food_y_cord,3);
            // Delete node from tail
            delete(t);
            // insert node next to head
            insert(t,snake_head_x_cord,snake_head_y_cord,3);
            rectangle(1,7,485,455);
            rectangle(3,9,483,453);
            gotoxy(65,10);
            printf("score:%d",score);
            delay(50);
            cleardevice();
        }
 
        if(dir==UP_DIRECTION)
        {
            snake_head_y_cord=snake_head_y_cord-6;
            display_snake(t);
            circle(food_x_cord,food_y_cord,3);
            // Delete node from tail
            delete(t);
            // insert node next to head
            insert(t,snake_head_x_cord,snake_head_y_cord,3);
            rectangle(1,7,485,455);
            rectangle(3,9,483,453);
            gotoxy(65,10);
            printf("score:%d",score);
            delay(50);
            cleardevice();
        }
 
        if(dir==DOWN_DIRECTION)
        {
            snake_head_y_cord=snake_head_y_cord+6;
            display_snake(t);
            circle(food_x_cord,food_y_cord,3);
            // Delete node from tail
            delete(t);
            // insert node next to head
            insert(t,snake_head_x_cord,snake_head_y_cord,3);
            rectangle(1,7,485,455);
            rectangle(3,9,483,453);
            gotoxy(65,10);
            printf("score:%d",score);
            delay(50);
            cleardevice();
        }
 
        s=t->front;
 
        while(s->next->next!=NULL)
        {
            // condtion to Check if snake hit the walls or himself
            if(s->x==(t->rear)->x&&s->y==(t->rear)->y||(t->rear)->x<6||(t->rear)->y<12||(t->rear)->x>480||(t->rear)->y>450)
            {
                // blick the screen if snake hits wall or himself
                for(i=0;i<5;i++)
                {
                    sound(4000);
                    delay(20);
                    nosound();
                    gotoxy(65,10);
                    printf("score:%d",score);
                    rectangle(1,7,485,455);
                    rectangle(3,9,483,453);
                    circle(food_x_cord,food_y_cord,3);
                    delay(280);
                    display_snake(t);
                    delay(300);
                    cleardevice();
                }
                goto end;
            }
        s=s->next;
        }
    }
    end:
        printf("\n\n\n\n\n\t\t\t\tEnd");
        getch();
}
