#include "rbtree.h"

#include <stdlib.h>
void fixed_del(rbtree* rt,node_t* t);
void check(rbtree* tr,node_t* t);
void lrotate(rbtree *tr,node_t* t);
void rrotate(rbtree *tr,node_t* t);
void transp(rbtree* rt,node_t* t1,node_t* t2);
rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)malloc(sizeof(rbtree));
  node_t *sent = (node_t*)malloc(sizeof(node_t));
  sent->color = RBTREE_BLACK;
  p->nil = sent;
  p->root = p->nil;
  // TODO: initialize struct if needed
  return p;
}
void delnode(rbtree *t,node_t *n){
  if(n->left != t->nil){
    delnode(t,n->left);
  }
  if(n->right != t->nil){
    delnode(t,n->right);
  }
  free(n);
}
void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  node_t* cur = t->root;
  if(cur != t->nil){
    delnode(t,t->root);
  }
  free(t->nil);
  t->nil = NULL;
  free(t);
  t = NULL;
  return;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *x = t->root;
  node_t *y = t->nil;
  node_t *nn = (node_t*)malloc(sizeof(node_t));
  nn->key = key;
  nn->left = t->nil;
  nn->right = t->nil;
  while(x !=t->nil){
    y = x;
    if(key<x->key){
      x = x->left;
    }else{
      x = x->right;
    }
  }
  nn->parent = y;
  if(y == t->nil){
    t->root = nn;
  }else if (key<y->key)
  {
    y->left = nn;
  }else{
    y->right = nn;
  }
  nn->color = RBTREE_RED;
  check(t,nn);
  return nn;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t *head = t->root;
  if(head == t->nil){
    return NULL;
  }
  while(head->key != key){
    if(head->key>key){
      head = head->left;
      if(head == t->nil){
        return NULL;
      }
    }
    else {
      head = head->right;
      if(head == t->nil){
        return NULL;
      }
    }
  }
  return head;
}

node_t *rbtree_min(const rbtree *t) {
  node_t *rn = t->root;
  while(rn->left!=t->nil){
    rn = rn->left;
  }
  return rn;
}

node_t *rbtree_max(const rbtree *t) {
  node_t *rn = t->root;
  while(rn->right!=t->nil){
    rn = rn->right;
  }
  return rn;
}

int rbtree_erase(rbtree *t, node_t *p) {
 node_t* y = p;
 node_t* x;
 color_t bcs = y->color;
 node_t* cur;
 if(p->left == t->nil){
  x = p->right;
  transp(t,p,p->right);
 }else if (p->right == t->nil)
 {
  x = p->left;
  transp(t,p,p->left);
 }else{
  cur = p->right;
  while(cur->left != t->nil){
    cur = cur->left;
  }
  y = cur;
  bcs = y->color;
  x = y->right;
  if(y != p->right){
    transp(t,y,y->right);
    y->right = p->right;
    y->right->parent = y;
  }else{
    x->parent = y;
  }
  transp(t,p,y);
  y->left =p->left;
  y->left->parent = y;
  y->color = p->color;
 }
 if(bcs == RBTREE_BLACK){
  fixed_del(t,x);
 }
 return 0;
}
node_t *get_next_node(const rbtree *t, node_t *p)
{
  node_t *current = p->right;
  if (current == t->nil) // 오른쪽 자식이 없으면
  {
    current = p;
    while (1)
    {
      if (current->parent->right == current) // current가 오른쪽 자식인 경우
        current = current->parent;           // 부모 노드로 이동 후 이어서 탐색
      else
        return current->parent; // current가 왼쪽 자식인 경우 부모 리턴
    }
  }
  while (current->left != t->nil) // 왼쪽 자식이 있으면
    current = current->left;      // 왼쪽 끝으로 이동
  return current;
}
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  node_t *current = rbtree_min(t);
  arr[0] = current->key;
  for (int i = 1; i < n; i++)
  {
    if (current == t->nil)
      break;                             // 노드가 끝까지 탐색된 경우 loop 탈출
    current = get_next_node(t, current); // 다음 노드로 이동
    if (current == t->nil)
      break;               // 노드가 끝까지 탐색된 경우 loop 탈출
    arr[i] = current->key; // 현재 노드의 key 값을 배열에 저장
  }
  return 0;
}
void rrotate(rbtree *tr,node_t* t){//오른쪽으로 회전
  if(t->left == tr->nil){
    return;
  }
  node_t *y = t->left;
  t->left = y->right;
  if(y->right != tr->nil){
    y->right->parent = t;
  }
  y->parent = t->parent;
  if(t->parent == tr->nil){
    tr->root = y;
  }else if (t == t->parent->left)
  {
    t->parent->left = y;
  }else{
    t->parent->right = y;
  }
  y->right = t;
  t->parent = y;
  }

void lrotate(rbtree *tr,node_t* t){//왼쪽으로 회전
  if(t->right == tr->nil){
    return;
  }
  node_t *y = t->right;
  t->right = y->left;
  if(y->left != tr->nil){
    y->left->parent = t;
  }
  y->parent = t->parent;
  if(t->parent == tr->nil){
    tr->root = y;
  }else if (t == t->parent->left)
  {
    t->parent->left = y;
  }else{
    t->parent->right = y;
  }
  y->left = t;
  t->parent = y;
}
void transp(rbtree* rt,node_t* t1,node_t* t2){
  if(t1->parent == rt->nil){
    rt->root = t2;
  }else if (t1 == t1->parent->left)
  {
    t1->parent->left = t2;
  }else{
    t1->parent->right = t2;
  }
  t2->parent = t1->parent;
}
void fixed_del(rbtree* rt,node_t* t){
  while(t!= rt->root && t->color == RBTREE_BLACK){
    if(t == t->parent->left){
      node_t* bro = t->parent->right;
      if(bro->color == RBTREE_RED){
        bro->color = RBTREE_BLACK;
        t->parent->color = RBTREE_RED;
        lrotate(rt,t->parent);
        bro = t->parent->right;
      }
      if(bro->left->color == RBTREE_BLACK && bro->right->color == RBTREE_BLACK){
        bro->color = RBTREE_RED;
        t=t->parent;
      }else{
        if(bro->right->color == RBTREE_BLACK){
          bro->left->color = RBTREE_BLACK;
          bro->color = RBTREE_RED;
          rrotate(rt,bro);
          bro = t->parent->right;
        }
        bro->color = t->parent->color;
        t->parent->color = RBTREE_BLACK;
        bro->right->color = RBTREE_BLACK;
        lrotate(rt,t->parent);
        t = rt->root;
      }
    }else{
      node_t* bro = t->parent->left;
      if(bro->color == RBTREE_RED){
        bro->color = RBTREE_BLACK;
        t->parent->color = RBTREE_RED;
        rrotate(rt,t->parent);
        bro = t->parent->left;
      }
      if(bro->right->color == RBTREE_BLACK && bro->left->color == RBTREE_BLACK){
        bro->color = RBTREE_RED;
        t=t->parent;
      }
      else{
        if(bro->left->color == RBTREE_BLACK){
          bro->right->color=RBTREE_BLACK;
          bro->color=RBTREE_RED;
          lrotate(rt,bro);
          bro = t->parent->left;
        }
        bro->color = t->parent->color;
        t->parent->color = RBTREE_BLACK;
        bro->left->color = RBTREE_BLACK;
        rrotate(rt,t->parent);
        t = rt->root;
      }
    }
  }
  t->color = RBTREE_BLACK;
}
void check(rbtree* tr,node_t* t){
  while(t->parent->color == RBTREE_RED){
    if(t->parent == t->parent->parent->left){
      node_t* uncle = t->parent->parent->right;
      if(uncle->color == RBTREE_RED){
        t->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        t->parent->parent->color = RBTREE_RED;
        t = t->parent->parent;
      }else{
        if(t == t->parent->right){
          t = t->parent;
          lrotate(tr,t);
        }
        t->parent->color = RBTREE_BLACK;
        t->parent->parent->color = RBTREE_RED;
        rrotate(tr,t->parent->parent);
      }
    }else{
      node_t *uncle = t->parent->parent->left;
      if(uncle->color == RBTREE_RED){
        t->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        t->parent->parent->color = RBTREE_RED;
        t = t->parent->parent;
      }else{
        if(t == t->parent->left){
          t = t->parent;
          rrotate(tr,t);
        }
        t->parent->color = RBTREE_BLACK;
        t->parent->parent->color = RBTREE_RED;
        lrotate(tr,t->parent->parent);
      }
    }
  }
  tr->root->color = RBTREE_BLACK;
}


