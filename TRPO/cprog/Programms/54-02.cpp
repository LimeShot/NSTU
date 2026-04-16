//------------------------------------------------------54-02.cpp
#include <stdio.h>
//------------------------------------------------------- 1
 struct man1 {
 char name[20];
 int dd,mm,yy;
 char *zodiak;
 man1 *next; } 
 A1= {"Петров",1,10,1969,"Весы",NULL },
 B1= {"Сидоров",8,9,1958,"Дева",&A1 },
 *p1 = &B1;
 void F1() { char c1,c2,c3,c4;
 c1 = A1.name[2]; c2 = B1.zodiak[3];
 c3 = p1->name[3]; c4 = p1->next->zodiak[1]; }
 //------------------------------------------------------- 2
 struct man2 {
 char name[20];
 char *zodiak;
 man2 *next;
      } C2[3] = {
      {"Петров","Весы",NULL },
      {"Сидоров","Дева",&C2[0] },
      {"Иванов","Козерог",&C2[1] }
 };
 void F2() { char c1,c2,c3,c4;
 c1 = C2[0].name[2];
 c2 = C2[1].zodiak[3];
 c3 = C2[2].next->name[3];
 c4 = C2[2].next->next->zodiak[1]; }
 //------------------------------------------------------- 3
 struct tree3 {
 int vv;
 tree3 *l,*r;
      } A3 = { 1,NULL,NULL },
 B3 = { 2,NULL,NULL },
 C3 = { 3, &A3, &B3 },
 D3 = { 4, &C3, NULL },
 *p3 = &D3;
 void F3() { int i1,i2,i3,i4;
 i1 =A3.vv; i2 = D3.l->vv;
 i3 =p3->l->r->vv; i4 = p3->vv; }
 //------------------------------------------------------- 4
 struct tree4 {
 int vv;
 tree4 *l,*r;
 } F[4] = 
      {{ 1,NULL,NULL },
      { 2,NULL,NULL },
      { 3, &F[0], &F[1] },
      { 4, &F[2], NULL }};
 void F4() { int i1,i2,i3,i4;
 i1 = F[0].vv; i2 = F[3].l->vv;
 i3 = F[3].l->r->vv; i4 = F[2].r->vv; }
 //------------------------------------------------------- 5
 struct list5 { 
 int vv;
 list5 *pred,*next;
 };
 extern list5 C5,B5,A5;
      list5 A5 = { 1, &C5, &B5 }, B5 = { 2, &A5, &C5 }, 
 C5 = { 3, &B5, &A5 }, *p5 = &A5;
 void F5() { int i1,i2,i3,i4;
 i1 = A5.next->vv; i2 = p5->next->next->vv;
 i3 = A5.pred->next->vv; i4 = p5->pred->pred->pred->vv; }
 //------------------------------------------------------ 6
 struct dat7 { int dd,mm,yy; } 
 aa = { 17,7,1977 },
 bb = { 22,7,1982 };
 struct man7 {
 char name[20];
 dat7 *pd;
 dat7 dd;
 char *zodiak; }
      A7= {"Петров", &aa, { 1,10,1969 }, "Весы" },
      B7= {"Сидоров", &bb, { 8,9,1958 }, "Дева" },
 *p7 = &B7;
 void F7() { int i1,i2,i3,i4;
 i1 = A7.dd.mm; i2 = A7.pd->yy;
 i3 = p7->dd.dd; i4 = p7->pd->yy; }
 //------------------------------------------------------ 7
 struct dat8 { int dd,mm,yy; };
 struct man8 {
 char name[20];
 dat8 dd[3];
      } A8[2] = {
                          {"Петров", {{1,10,1969},{8,8,1988},{3,2,1978}}},
                          {"Иванов",{{8,12,1958},{12,3,1976},{3,12,1967}}}
 };
 void F8() { int i1,i2; 
 i1 = A8[0].dd[0].mm; i2 = A8[1].dd[2].dd; }
 //------------------------------------------------------ 8
 struct man9 {
 char name[20];
 char *zodiak;
 man9 *next;
      } A9= {"Петров","Весы",NULL },
 B9= {"Сидоров","Дева",&A9 },
 *p9[4] = { &B9, &A9, &A9, &B9 };
 void F9() { char c1,c2,c3,c4;
 c1 = p9[0]->name[2]; c2 = p9[2]->zodiak[3];
 c3 = p9[3]->next->name[3]; c4 = p9[0]->next->zodiak[1]; } 
