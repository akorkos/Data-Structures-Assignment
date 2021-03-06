#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree() {
    root = nullptr; // αρχικοποίηση της ρίζας, σημαίνει πως το δένδρο δεν δημιουργηθεί ακόμα
}

BinarySearchTree::~BinarySearchTree() {
    destroy(root);
}

bool BinarySearchTree::insert(string key) {
    if (root == nullptr) { //εάν η ρίζα είναι κενή, δηλ. το δένδρο δεν έχει δημιουργηθεί ακόμα γίνεται αρχικοποίηση των πεδίων του struct
        root = new node;
        root->word = key;
        root->appearances = 1;
        root->parent = nullptr;
        root->right = nullptr;
        root->left = nullptr;
        return true;
    } else
        return insert(root, key);
}

bool BinarySearchTree::insert(node *rt, string key) {
    if (key == rt->word) { //εάν η λέξη που πρόκειται να εισαχθεί υπάρχει ήδη αυξάνεται η συχνότητα εμφάνισης της λέξης
        rt->appearances++;
        return true;
    }

    //εάν η λέξη που πρόκειται να εισαχθεί είναι λεξικογραφικά μεγαλύτερη τοποθετείτε στο δεξί κόμβο και γίνεται αρχικοποίηση των πεδίων του struct
    if (key > rt->word) {
        if (rt->right == nullptr) {
            rt->right = new node;
            rt->right->word = key;
            rt->right->appearances = 1;
            rt->right->parent = rt;
            rt->right->right = nullptr;
            rt->right->left = nullptr;
            return true;
        }
        return insert(rt->right, key);
    } else { //εάν η λέξη που πρόκειται να εισαχθεί είναι λεξικογραφικά μικρότερη τοποθετείτε στο αριστερο κόμβο και γίνεται αρχικοποίηση των πεδίων του struct
        if (rt->left == nullptr) {
            rt->left = new node;
            rt->left->word = key;
            rt->left->appearances = 1;
            rt->left->parent = rt;
            rt->left->right = nullptr;
            rt->left->left = nullptr;
            return true;
        }
        return insert(rt->left, key);
    }
}

/*
Πρόκειται για την μέθοδο αναζήτησης που χρησιμοποιείται από τον χρήστη.
Εάν η λέξη εμφανίζεται μέσα στον πίνακα επιστρέφεται ο αριθμός των εμφανίσεων διαφορετικά, επιστρέφεται η τιμή 0
*/
int BinarySearchTree::search(string key) {
    node *pos = privSearch(key); //καλεί την αντίστοιχη private μέθοδο
    if (pos == nullptr) {
        return 0;
    } else
        return pos->appearances;
}

//αναζήτηση κόμβου με τη λέξη key
node *BinarySearchTree::privSearch(string key) {
    node *pos = root;
    while (pos != nullptr && key != pos->word) {
        if (key > pos->word)
            pos = pos->right;
        else
            pos = pos->left;
    }
    return pos;
}

//διαγραφή κόμβου από το δέντρο
bool BinarySearchTree::remove(node *rt) {
    node *parent = rt->parent;
    //έλεγχος αν ο κόμβος έχει παιδιά
    if (rt->left == nullptr && rt->right == nullptr) { //διαγραφη κόμβου με κανενα παιδί
        if (parent == nullptr) { //έλεγχος αν ο κόμβος είναι κενός
            delete (rt);
            root = nullptr;
        } else if (parent->left == rt) {
            delete (parent->left);
            parent->left = nullptr;
        } else {
            delete (parent->right);
            parent->right = nullptr;
        }
    } else if (rt->left == nullptr || rt->right == nullptr) { //διαγραφη κόμβου με ένα παιδί
        if (parent == nullptr) { //έλεγχος αν ο κόμβος είναι κενός
            if (rt->left == nullptr)
                root = rt->right;
            else
                root = rt->left;
            delete (rt);
        } else if (parent->left == rt) {
            if (rt->left == nullptr)
                parent->left = rt->right;
            else
                parent->left = rt->left;
            delete (rt);
        } else {
            if (rt->left == nullptr)
                parent->right = rt->right;
            else
                parent->right = rt->left;
            delete (rt);
        }
    } else { //διαγραφη κόμβου με δύο παιδιά
        node *successor = minimum(rt->right);
        rt->word = successor->word;
        rt->appearances = successor->appearances;
        remove(successor);
    }
    return true;
}

bool BinarySearchTree::remove(string key) {
    node *hasChild = privSearch(key);
    if (hasChild == nullptr) //έλεγχος αν υπάρχει κόμβος με τη λέξη key
        return false;
    else
        return remove(hasChild); //καλεί την αντίστοιχη private μέθοδο για τη διαγραφή κόμβου
}

//ψάχνει αν υπάρχει αριστερό παιδί
//αν δεν έχει αριστερό παιδί, επιστρέφει τον κόμβο που δίνεται σαν παράμετρος (current node)
node *BinarySearchTree::minimum(node *rt) {
    while (rt->left != nullptr)
        rt = rt->left;
    return rt;
}

void BinarySearchTree::inOrder(node *pos) {
    if (pos == nullptr)
        return;

    inOrder(pos->left);
    cout << pos->word << " : " << pos->appearances << endl;
    inOrder(pos->right);
}

void BinarySearchTree::printInOrder() {
    inOrder(root); //καλεί την αντίστοιχη private μέθοδο για εκτύπωση των κόμβων με in-order
}

void BinarySearchTree::preOrder(node *pos) {
    if (pos == nullptr)
        return;

    cout << pos->word << " : " << pos->appearances << endl;
    preOrder(pos->left);
    preOrder(pos->right);
}

void BinarySearchTree::printPreOrder() {
    preOrder(root); //καλεί την αντίστοιχη private μέθοδο για εκτύπωση των κόμβων με pre-order
}

void BinarySearchTree::postOrder(node *pos) {
    if (pos == nullptr)
        return;

    postOrder(pos->left);
    postOrder(pos->right);
    cout << pos->word << " : " << pos->appearances << endl;
}

void BinarySearchTree::printPostOrder() {
    postOrder(root); //καλεί την αντίστοιχη private μέθοδο για εκτύπωση των κόμβων με post-order
}

//χρησιμοποιείται στο καταστροφέα
//καταστροφή παιδιών και μετά καταστροφή ρίζας (αναδρομικά)
void BinarySearchTree::destroy(node *rt) {
    if (rt != nullptr) {
        destroy(rt->left);
        destroy(rt->right);
        delete (rt);
    } 
}
