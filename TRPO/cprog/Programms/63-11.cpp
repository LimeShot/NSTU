 //-----------------------------------------------------63-11.cpp
 #include <stdio.h>
 struct list { int val; list *next,*prev; };
 //------------------------------------------------------- 1
 int F1(list *p) 
 { int n;
 for (n=0; p!=NULL; p=p->next, n++);
 return n; }
 //------------------------------------------------------- 2
 list *F2(list *ph, int v)
 { list *q = new list;
 q->val = v; q->next = ph; ph = q;
 return ph; }
 //------------------------------------------------------- 3
 list *F3(list *p, int n) 
 { for (; n!=0 && p!=NULL; n--, p=p->next);
 return p; }
 //------------------------------------------------------- 4
 list *F4(list *ph, int v)
 { list *p,*q = new list;
 q->val = v; q->next = NULL; 
 if (ph == NULL) return q;
 for ( p=ph ; p ->next !=NULL; p = p->next);
 p ->next = q; return ph; }
 //------------------------------------------------------- 5
 list *F5(list *ph, int n)
 { list *q ,*pr,*p; 
 for ( p=ph,pr=NULL; n!=0 && p!=NULL; n--, pr=p, p =p->next);
 if (p==NULL) return ph;
      if (pr==NULL) { q=ph; ph=ph->next; }
      else { q=p; pr->next=p->next; }
 delete q; 
 return ph; }
 //------------------------------------------------------- 6
 int F6(list *p)
 { int n; list *q;
 if (p==NULL) return 0;
 for (q = p, p = p->next, n=1; p !=q; p=p->next, n++);
 return n; }
 //------------------------------------------------------- 7
 list *F7(list *p, int v)
 { list *q;
 q = new list;
 q->val = v; q->next = q->prev = q;
 if (p == NULL) p = q;
 else
      { q->next = p; q->prev = p->prev;
      p->prev->next = q; p->prev = q; p=q;
      } 
 return p; }
 //------------------------------------------------------- 8
 list *F8(list *ph) 
 { list *q, *out, *p , *pr;
 out = NULL; 
 while (ph !=NULL) 
      { q = ph; ph = ph->next; 
      for ( p=out,pr=NULL; p!=NULL && q->val>p->val; pr=p,p=p->next); 
      if (pr==NULL) 
           { q->next=out; out=q; }
      else 
           { q->next=p; pr->next=q; }
      } return out; } 
 //------------------------------------------------------- 9
 list *F9(list *pp, int n)
 { list *q;
 for (q = pp; n!=0; q = q->next, n--);
      if (q->next == q) { delete q; return NULL; }
 if (q == pp) pp = q->next;
 q->prev->next = q->next;
 q->next->prev = q->prev;
 delete q; return pp; }
 //------------------------------------------------------ 10
 list *F10(list *ph, int v)
 { list *q ,*pr,*p; 
 q=new list; q->val=v; q->next=NULL;
 if (ph==NULL) return q;
 for ( p=ph,pr=NULL; p!=NULL && v>p->val; pr=p,p=p->next); 
      if (pr==NULL) { q->next=ph; ph=q; }
      else { q->next=p; pr->next=q; }
 return ph; }
 //------------------------------------------------------ 11
 list *F11(list *ph, int v)
 { list *q = new list;
 q->val = v; q->next = q->prev = q;
 if (ph == NULL) return q;
 list *p = ph;
      do { 
      if (v < p->val) break;
      p=p->next;
      } while (p!=ph);
 q->next = p; q->prev = p->prev;
 p->prev->next = q; p->prev = q;
 if ( ph->val > v) ph=q;
 return ph; }
 //------------------------------------------------------ 12
 void F12(list *&ph, int v, int n)
 { list *q = new list;
 int n0=n;
 q->val = v; q->next = q->prev = q;
 if (ph == NULL) { ph=q; return; }
 list *p;
 for (p=ph; n--!=0; p=p->next);
 q->next = p; q->prev = p->prev;
 p->prev->next = q; p->prev = q;
 if ( n0==0) ph=q; }
