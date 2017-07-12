#include<stdio.h>
#include<stdlib.h>
typedef struct e_node_tag
{
    int data;
    int rownum;
    int colnum;
    struct e_node_tag* next;
    struct e_node_tag* down;
}e_node;

typedef struct col_node_tag
{
    int colnum;
    struct col_node_tag* next;
    e_node* down;
}c_node;

typedef struct row_node_tag
{
    int rownum;
    struct row_node_tag* down;
    e_node* next;
}r_node;

typedef struct sm_node_tag
{
    c_node* next;
    r_node* down;
}sm_node;

void InitializeSM(sm_node* smtop);
void PopulateSM(sm_node* smtop);
void InsertSM(sm_node* smtop, int r, int c, int d);
void PrintSM(sm_node* smtop);
void DeleteSM(sm_node* smtop,int r, int c, int *dptr);

void InitializeSM(sm_node* smtop)
{
    smtop->next=NULL;
    smtop->down=NULL;
}

void PopulateSM(sm_node* smtop)
{
    int r,c,d;
    FILE* fptr=fopen("smdata.txt","r");
    while(!feof(fptr))
    {
        fscanf(fptr,"%d",&r);
        fscanf(fptr,"%d",&c);
        fscanf(fptr,"%d",&d);
        InsertSM(smtop,r,c,d);
    }
}

void InsertSM(sm_node* smtop, int r, int c, int d)
{
    if(smtop==NULL)
    {
        printf("\nNULL Sparce Matrix\n");
    }
    else
    {
        if(smtop->next==NULL||smtop->down==NULL)
        {
            e_node* enptr=(e_node*)malloc(sizeof(e_node));
            enptr->data=d;
            enptr->rownum=r;
            enptr->colnum=c;
            enptr->next=NULL;
            enptr->down=NULL;
            c_node* cnptr=(c_node*)malloc(sizeof(c_node));
            cnptr->colnum=c;
            cnptr->next=NULL;
            r_node* rnptr=(r_node*)malloc(sizeof(r_node));
            rnptr->rownum=r;
            rnptr->down=NULL;

            smtop->next=cnptr;
            smtop->down=rnptr;
            cnptr->down=enptr;
            rnptr->next=enptr;

        }
        else if((smtop->next)->colnum>c||(smtop->down)->rownum>r)
        {
            if((smtop->next)->colnum>c&&(smtop->down)->rownum>r)
            {
                e_node* enptr=(e_node*)malloc(sizeof(e_node));
                enptr->data=d;
                enptr->rownum=r;
                enptr->colnum=c;
                enptr->next=NULL;
                enptr->down=NULL;
                c_node* cnptr=(c_node*)malloc(sizeof(c_node));
                cnptr->colnum=c;
                cnptr->next=NULL;
                r_node* rnptr=(r_node*)malloc(sizeof(r_node));
                rnptr->rownum=r;
                rnptr->down=NULL;

                cnptr->next=smtop->next;
                smtop->next=cnptr;
                rnptr->down=smtop->down;
                smtop->down=rnptr;
                cnptr->down=enptr;
                rnptr->next=enptr;
            }
            else if((smtop->next)->colnum>c&&(smtop->down)->rownum<=r)
            {
                e_node* enptr=(e_node*)malloc(sizeof(e_node));
                enptr->data=d;
                enptr->rownum=r;
                enptr->colnum=c;
                enptr->next=NULL;
                enptr->down=NULL;
                c_node* cnptr=(c_node*)malloc(sizeof(c_node));
                cnptr->colnum=c;
                cnptr->next=smtop->next;
                smtop->next=cnptr;

                r_node* rptr=smtop->down;
                while(rptr->down!=NULL&&(rptr->down)->rownum<=r)
                {
                    rptr=rptr->down;
                }
                if(rptr->rownum==r)
                {
                    if((rptr->next)->colnum>c)
                    {
                        enptr->next=rptr->next;
                        rptr->next=enptr;
                        cnptr->down=enptr;
                    }
                    else
                    {
                        e_node* eptr=rptr->next;
                        while((eptr->next)->colnum<c&&eptr->next!=NULL)
                        {
                            eptr=eptr->next;
                        }
                        enptr->next=eptr->next;
                        eptr->next=enptr;
                        cnptr->down=enptr;
                    }
                }
                else
                {
                    r_node* rnptr=(r_node*)malloc(sizeof(r_node));
                    rnptr->rownum=r;
                    rnptr->down=rptr->down;
                    rptr->down=rnptr;
                    rptr->next=enptr;
                    cnptr->down=enptr;
                }
            }
            else if((smtop->next)->colnum<=c&&(smtop->down)->rownum>r)
            {
                e_node* enptr=(e_node*)malloc(sizeof(e_node));
                enptr->data=d;
                enptr->rownum=r;
                enptr->colnum=c;
                enptr->next=NULL;
                enptr->down=NULL;
                r_node* rnptr=(r_node*)malloc(sizeof(r_node));
                rnptr->rownum=r;
                rnptr->down=smtop->down;
                smtop->down=rnptr;

                c_node* cptr=smtop->next;
                while(cptr->next!=NULL&&(cptr->next)->colnum<=c)
                {
                    cptr=cptr->next;
                }
                if(cptr->colnum==c)
                {
                    if((cptr->down)->rownum>r)
                    {
                        enptr->down=cptr->down;
                        cptr->down=enptr;
                        rnptr->next=enptr;
                    }
                    else
                    {
                        e_node* eptr=cptr->down;
                        while(eptr->down!=NULL&&(eptr->down)->rownum<r)
                        {
                            eptr=eptr->down;
                        }
                        enptr->down=eptr->down;
                        eptr->down=enptr;
                        rnptr->next=enptr;
                    }
                }
                else
                {
                    c_node* cnptr=(c_node*)malloc(sizeof(c_node));
                    cnptr->colnum=c;
                    cnptr->next=cptr->next;
                    cptr->next=cnptr;
                    cnptr->down=enptr;
                    rnptr->next=enptr;
                }
            }
        }
        else
        {
            r_node* rptr=smtop->down;
            c_node*cptr=smtop->next;
            while(cptr->next!=NULL&&(cptr->next)->colnum<=c)
            {
                cptr=cptr->next;
            }
            while(rptr->down!=NULL&&(rptr->down)->rownum<=r)
            {
                rptr=rptr->down;
            }

            if(cptr->colnum==c&&rptr->rownum==r)
            {
                if((cptr->down)->rownum>r||(rptr->next)->colnum>c)
                {
                    if((cptr->down)->rownum>r&&(rptr->next)->colnum>c)
                    {
                        e_node* enptr=(e_node*)malloc(sizeof(e_node));
                        enptr->data=d;
                        enptr->rownum=r;
                        enptr->colnum=c;
                        enptr->next=rptr->next;
                        rptr->next=enptr;
                        enptr->down=cptr->down;
                        cptr->down=enptr;
                    }
                    else if((cptr->down)->rownum>r&&(rptr->next)->colnum<=c)
                    {
                        e_node* enptr=(e_node*)malloc(sizeof(e_node));
                        enptr->data=d;
                        enptr->rownum=r;
                        enptr->colnum=c;
                        enptr->down=cptr->down;
                        cptr->down=enptr;
                        e_node* eptr=rptr->next;
                        while(eptr->next!=NULL&&(eptr->next)->colnum<c)
                        {
                            eptr=eptr->next;
                        }
                        enptr->next=eptr->next;
                        eptr->next=enptr;
                    }
                    else
                    {
                        e_node* enptr=(e_node*)malloc(sizeof(e_node));
                        enptr->data=d;
                        enptr->rownum=r;
                        enptr->colnum=c;
                        enptr->next=rptr->next;
                        rptr->next=enptr;
                        e_node* eptr=cptr->down;
                        while(eptr->down!=NULL&&(eptr->down)->rownum<r)
                        {
                            eptr=eptr->down;
                        }
                        enptr->down=eptr->down;
                        eptr->down=enptr;
                    }
                }
                else
                {
                    e_node* ecptr=cptr->down;
                    e_node* erptr=rptr->next;
                    while(ecptr->down!=NULL&&(ecptr->down)->rownum<=r)
                    {
                        ecptr=ecptr->down;
                    }
                    while(erptr->next!=NULL&&(erptr->next)->colnum<c)
                    {
                        erptr=erptr->next;
                    }
                    if(ecptr==erptr)
                    {
                        ecptr->data=d;
                    }
                    else
                    {
                        e_node* enptr=(e_node*)malloc(sizeof(e_node));
                        enptr->data=d;
                        enptr->rownum=r;
                        enptr->colnum=c;
                        enptr->down=ecptr->down;
                        ecptr->down=enptr;
                        enptr->next=erptr->next;
                        erptr->next=enptr;
                    }
                }
            }
            else if(cptr->colnum==c&&rptr->rownum<r)
            {
                r_node* rnptr=(r_node*)malloc(sizeof(r_node));
                rnptr->rownum=r;
                rnptr->down=rptr->down;
                rptr->down=rnptr;

                if((cptr->down)->rownum>r)
                {
                    e_node* enptr=(e_node*)malloc(sizeof(e_node));
                    enptr->data=d;
                    enptr->rownum=r;
                    enptr->colnum=c;
                    enptr->down=cptr->down;
                    enptr->next=NULL;
                    cptr->down=enptr;
                    rnptr->next=enptr;
                }
                else
                {
                    e_node* eptr=cptr->down;
                    while(eptr->down!=NULL&&(eptr->down)->rownum<r)
                    {
                        eptr=eptr->down;
                    }
                    e_node* enptr=(e_node*)malloc(sizeof(e_node));
                    enptr->data=d;
                    enptr->rownum=r;
                    enptr->colnum=c;
                    enptr->next=NULL;
                    enptr->down=eptr->down;
                    eptr->down=enptr;
                    rnptr->next=enptr;
                }
            }
            else if(cptr->colnum<c&&rptr->rownum==r)
            {
                e_node* enptr=(e_node*)malloc(sizeof(e_node));
                enptr->data=d;
                enptr->rownum=r;
                enptr->colnum=c;
                enptr->down=NULL;
                c_node* cnptr=(c_node*)malloc(sizeof(c_node));
                cnptr->colnum=c;
                cnptr->next=cptr->next;
                cptr->next=cnptr;
                cnptr->down=enptr;

                if((rptr->next)->colnum>c)
                {
                    enptr->next=rptr->next;
                    rptr->next=enptr;
                }
                else
                {
                    e_node* eptr=rptr->next;
                    while(eptr->next!=NULL&&(eptr->next)->colnum<c)
                    {
                        eptr=eptr->next;
                    }
                    enptr->next=eptr->next;
                    eptr->next=enptr;
                }
            }
            else
            {
                e_node* enptr=(e_node*)malloc(sizeof(e_node));
                enptr->data=d;
                enptr->rownum=r;
                enptr->colnum=c;
                enptr->down=NULL;
                enptr->next=NULL;
                c_node* cnptr=(c_node*)malloc(sizeof(c_node));
                cnptr->colnum=c;
                cnptr->down=enptr;
                cnptr->next=cptr->next;
                cptr->next=cnptr;
                r_node* rnptr=(r_node*)malloc(sizeof(r_node));
                rnptr->rownum=r;
                rnptr->next=enptr;
                rnptr->down=rptr->down;
                rptr->down=rnptr;
            }
        }
    }
}

void PrintSM(sm_node* smtop)
{
    e_node* eptr;
    r_node* rptr;
    if(smtop==NULL)
    {
        printf("\nNULL SparceMatrix\n");
    }
    else if(smtop->next==NULL||smtop->down==NULL)
    {
        printf("\nEmpty SparceMatrix\n");
    }
    else
    {
        for(rptr=smtop->down;rptr!=NULL;rptr=rptr->down)
        {
            printf("\n");
            for(eptr=rptr->next;eptr!=NULL;eptr=eptr->next)
            {
                printf("(%d,%d):%d,  ",eptr->rownum, eptr->colnum, eptr->data);
            }
        }
        printf("\nEND");
    }
}

void DeleteSM(sm_node* smtop,int r, int c, int *dptr)
{
    if(smtop==NULL)
    {
        printf("\nNULL SpareceMatrix\n");
    }
    else if(smtop->next==NULL||smtop->down==NULL)
    {
        printf("\nEMPTY SparceMatrix\n");
    }
    else
    {
        r_node* rptprev,*rptr=smtop->down;
        while(rptr->down!=NULL&&rptr->rownum!=r)
        {
            rptprev=rptr;
            rptr=rptr->down;
        }
        if(rptr->rownum==r)
        {
            c_node* cptprev,*cptr=smtop->next;
            while(cptr->next!=NULL&&cptr->colnum!=c)
            {
                cptprev=cptr;
                cptr=cptr->next;
            }
            if(cptr->colnum==c)
            {
                if((cptr->down)->rownum==r)
                {
                    if((rptr->next)->colnum==c)
                    {
                        e_node* etemp=rptr->next;
                        rptr->next=(rptr->next)->next;
                        cptr->down=(cptr->down)->down;
                        *dptr=etemp->data;
                        free(etemp);
                        if(cptr->down==NULL&&rptr->next==NULL)
                        {
                            if(smtop->next==cptr||smtop->down==rptr)
                            {
                                if(smtop->next==cptr&&smtop->down==rptr)
                                {
                                    smtop->down=(smtop->down)->down;
                                    smtop->next=(smtop->next)->next;
                                    free(cptr);
                                    free(rptr);
                                }
                                else if(smtop->next==cptr)
                                {
                                    smtop->next=(smtop->next)->next;
                                    rptprev->down=rptr->down;
                                    free(rptr);
                                }
                                else
                                {
                                    smtop->down=(smtop->down)->down;
                                    cptprev->next=cptr->next;
                                    free(cptr);
                                }
                            }
                            else
                            {
                                cptprev->next=cptr->next;
                                free(cptr);
                                rptprev->down=rptr->down;
                                free(rptr);
                            }
                        }
                        else if(cptr->down==NULL||rptr->next==NULL)
                        {
                            if(cptr->down==NULL)
                            {
                                if(smtop->next==cptr)
                                {
                                    smtop->next=(smtop->next)->next;
                                    free(cptr);
                                }
                                else
                                {
                                    cptprev->next=cptr->next;
                                    free(cptr);
                                }
                            }
                            else
                            {
                                if(smtop->down==rptr)
                                {
                                    smtop->down=(smtop->down)->down;
                                    free(rptr);
                                }
                                else
                                {
                                    rptprev->down=rptr->down;
                                    free(rptr);
                                }
                            }
                        }

                    }
                    else
                    {
                       e_node* eptprev,*eptr=rptr->next;
                       while(eptr->next!=NULL&&eptr->colnum!=c)
                       {
                           eptprev=eptr;
                           eptr=eptr->next;
                       }
                       if(eptr->colnum==c)
                       {
                           eptprev->next=eptr->next;
                           *dptr=eptr->data;
                           free(eptr);
                       }
                       else
                       {
                           printf("\nNo data node as such exists\n");
                       }
                    }
                }
                else
                {
                    e_node* eptprev,*eptr=cptr->down;
                    while(eptr->down!=NULL&&eptr->rownum<r)
                    {
                        eptprev=eptr;
                        eptr=eptr->down;
                    }
                    if(eptr->rownum==r)
                    {
                        if((rptr->next)->colnum==c)
                        {
                            rptr->next=(rptr->next)->next;
                            *dptr=eptr->data;
                            eptprev->down=eptr->down;
                            free(eptr);
                            if(rptr->next==NULL)
                            {
                                rptprev->down=rptr->down;
                                free(rptr);
                            }
                        }
                        else
                        {
                            e_node* erptr=rptr->next;
                            while((erptr->next)->colnum!=c)
                            {
                                erptr=erptr->next;
                            }
                            erptr->next=(erptr->next)->next;
                            *dptr=eptr->data;
                            eptprev=eptr->down;
                            free(eptr);
                        }
                    }
                    else
                    {
                        printf("\nNo data node as such exists\n");
                    }
                }
            }
            else
            {
                printf("\n%d-Coloumn doesn't even eist\n",c);
            }
        }
        else
        {
            printf("\n%d-Row dowsn't even exist\n",r);
        }
    }
}

void main()
{
    int r,c,d,yn=1;
    sm_node smtop;
    InitializeSM(&smtop);
    PopulateSM(&smtop);
    PrintSM(&smtop);

    while(yn==1)
    {
        printf("\nEnter the Row Coloumn Data you want to insert\n");
        scanf("%d%d%d",&r,&c,&d);
        InsertSM(&smtop,r,c,d);
        PrintSM(&smtop);
        printf("\nDo you want to insert again\n1:YES\n0:NO?\n");
        scanf("%d",&yn);
    }

    yn=1;

    while(yn==1)
    {
        printf("\nEnter the Row Coloumn you want to delete\n");
        scanf("%d%d",&r,&c);
        DeleteSM(&smtop,r,c,&d);
        PrintSM(&smtop);
        printf("\nDo you want to delete again\n1:YES\n0:NO?\n");
        scanf("%d",&yn);
    }

}
