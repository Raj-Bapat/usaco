#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;

struct item {
    long long key, prior, cnt = 0;
    item * l, * r;
    item() { }
    item (long long key, long long prior) : key(key), prior(prior), l(NULL), r(NULL) { }
};
typedef item * pitem;

long long cnt (pitem t) {
    return t ? t->cnt : 0;
}

void upd_cnt (pitem t) {
    if (t)
        t->cnt = 1 + cnt(t->l) + cnt (t->r);
}

void split (pitem t, long long key, pitem & l, pitem & r) {
    if (!t) {
        l = r = NULL;
    } else if (key < t->key) {
        split (t->l, key, l, t->l);
        r = t;
    } else {
        split (t->r, key, t->r, r);
        l = t;
    }
    upd_cnt(t);
}

void inserttree (pitem & t, pitem it) {
    if (!t) {
        t = it;
    } else if (it->prior > t->prior) {
        split (t, it->key, it->l, it->r);
        t = it;
    } else {
        inserttree (it->key < t->key ? t->l : t->r, it);
    }
    upd_cnt(t);
}

void merge (pitem & t, pitem l, pitem r) {
    if (!l || !r) {
        t = l ? l : r;
    } else if (l->prior > r->prior) {
        merge (l->r, l->r, r);
        t = l;
    } else {
        merge (r->l, l, r->l);
        t = r;
    }
    upd_cnt(t);
}

void erasenode (pitem & t, long long key) {
    if (t->key == key)
        merge (t, t->l, t->r);
    else
        erasenode(key < t->key ? t->l : t->r, key);
    upd_cnt(t);
}

pitem unite (pitem l, pitem r) {
    if (!l || !r)  return l ? l : r;
    if (l->prior < r->prior)  swap (l, r);
    pitem lt, rt;
    split (r, l->key, lt, rt);
    l->l = unite (l->l, lt);
    l->r = unite (l->r, rt);
    return l;
}

void inorder(pitem t) {
    if (t) {
        inorder(t->l);
        cout << "key: "<< t->key << " | priority: " << t->prior << " | cnt: " << t->cnt << endl;
        if (t->l)
            cout << " | left child: " << t->l->key;
        if (t->r)
            cout << " | right child: " << t->r->key;
        cout << endl;
        inorder(t->r);
    }
}

pitem searchtree(pitem root, long long key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    if (root->key < key) {
        return searchtree(root->r, key);
    }
    return searchtree(root->l, key);
}

pitem findith(pitem x, long long i) {
    long long r = cnt(x->l) + 1;
    if (r == i) {
        return x;
    } else if (i<r) {
        return findith(x->l, i);
    } else {
        return findith(x->r, i-r);
    }
}

long long findrank(pitem x, long long target) {
    long long r = cnt(x->l) + 1;
    if (x->key == target) {
        return r;
    } else if (target<x->key) {
        return findrank(x->l, target);
    } else {
        return r+findrank(x->r, target);
    }
}

int main() {
    srand(time(NULL));
    pitem root = NULL;
    return 0;
}






















//    cout << findrank(root, 20) << endl;
//    cout << findrank(root, 30) << endl;
//    cout << findrank(root, 40) << endl;
//    cout << findrank(root, 50) << endl;
//    cout << findrank(root, 60) << endl;
//    cout << findrank(root, 70) << endl;
//    cout << findrank(root, 80) << endl;

//    cout << findith(root, 1)->key << endl;
//    cout << findith(root, 2)->key << endl;
//    cout << findith(root, 3)->key << endl;
//    cout << findith(root, 4)->key << endl;
//    cout << findith(root, 5)->key << endl;
//    cout << findith(root, 6)->key << endl;
//    cout << findith(root, 7)->key << endl;
//    inserttree(root, new struct item(50, rand()));
//    inserttree(root, new struct item(30, rand()));
//    inserttree(root, new struct item(20, rand()));
//    inserttree(root, new struct item(40, rand()));
//    inserttree(root, new struct item(70, rand()));
//    inserttree(root, new struct item(60, rand()));
//    inserttree(root, new struct item(80, rand()));
//    cout << "Inorder traversal of the given tree \n";
//    inorder(root);
//    cout << "\nDelete 20\n";
//    erasenode(root, 20);
//    cout << "Inorder traversal of the modified tree \n";
//    inorder(root);
//    cout << "\nDelete 30\n";
//    erasenode(root, 30);
//    cout << "Inorder traversal of the modified tree \n";
//    inorder(root);
//    cout << "\nDelete 50\n";
//    erasenode(root, 50);
//    cout << "Inorder traversal of the modified tree \n";
//    inorder(root);
//    pitem res = searchtree(root, 70);
//    (res == NULL)? cout << "\n50 Not Found ":
//    cout << "\n50 found";

