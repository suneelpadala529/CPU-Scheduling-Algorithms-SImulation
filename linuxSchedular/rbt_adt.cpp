#include<iostream>
#include<random>

#define RED 1
#define BLACK 0

using namespace std;

typedef struct RB_NODE
{
    int v_time, p_id, a_time, b_time, nice_value, weight, time_slice;
    int color;
    struct RB_NODE *parent, *right, *left;
}RBT_NODE;

class RB_TREE
{
    public:
        RBT_NODE *root = new RBT_NODE();
        RB_TREE()
        {
            root = NULL;
        }
        void print_rbt_pre(RBT_NODE *);
        void print_rbt(RBT_NODE *);
        RBT_NODE* double_black_check(RBT_NODE *);

        void insert_to_RB(RBT_NODE *, int, int , int , int, int, int, int);
        //Insertion Requiremnts
        RBT_NODE *insert_bst(RBT_NODE *, RBT_NODE * );
        void check_RBT_properties(RBT_NODE *);
        void left_rotate(RBT_NODE *);
        void right_rotate(RBT_NODE *);

        void rbt_deletion(RBT_NODE *);
        //Deletion Requiremnts
        RBT_NODE *delete_process(RBT_NODE *);
        RBT_NODE *search_process(RBT_NODE *, int );
        RBT_NODE *inorder_successor(RBT_NODE *);
        RBT_NODE *find_inorder_successor(RBT_NODE *);
        RBT_NODE *inorder_predecessor(RBT_NODE *);
        RBT_NODE *find_inorder_predecessor(RBT_NODE *);

        //deletion cases
        RBT_NODE *right_case_3(RBT_NODE *, RBT_NODE *);
        RBT_NODE *right_case_6(RBT_NODE *, RBT_NODE *);
        RBT_NODE *left_case_3(RBT_NODE *, RBT_NODE *);
        RBT_NODE *left_case_6(RBT_NODE *, RBT_NODE *);

        RBT_NODE *get_min_vtime_process(RBT_NODE *);
        RBT_NODE *find_min(RBT_NODE *);

        int *gaussiandistribution(int n, int mean, int stdev);

};

void RB_TREE::insert_to_RB(RBT_NODE *rb_root, int p_id, int v_time, int a_time, int b_time, int n_value, int weight, int t_slice) 
{
    
    RBT_NODE *new_node = new RBT_NODE();
    new_node->color = RED;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->v_time = v_time;
    new_node->p_id = p_id;
    new_node->a_time = a_time;
    new_node->b_time = b_time;
    new_node->nice_value = n_value;
    new_node->weight = weight;
    new_node->time_slice = t_slice;
    
    if(rb_root == NULL)
    {
        root = new_node;
        new_node->color = BLACK;
    }
    else
    {
        insert_bst(rb_root, new_node);
        check_RBT_properties(new_node);
    }
}

RBT_NODE* RB_TREE::double_black_check(RBT_NODE *del_process)
{
    if(del_process->color == BLACK)
    {
        RBT_NODE *DB = new RBT_NODE();
        DB = del_process;
        // DB->parent = del_process->parent;
        // if(del_process->parent->left == del_process)
        //     del_process->parent->left = DB;
        // else if(del_process->parent->right == del_process)
        //     del_process->parent->right = DB;
        return DB;
    }
    else
    {
        // cout<<"\n Process deleting is "<<del_process->p_id<<" and v time "<<del_process->v_time;
        if(del_process->parent->left == del_process)
            del_process->parent->left = NULL;
        else if(del_process->parent->right == del_process)
            del_process->parent->right = NULL;
        free(del_process);
        return NULL;
    }
}

RBT_NODE* RB_TREE::insert_bst(RBT_NODE *t_root, RBT_NODE *node)
{
    if(t_root == NULL)
    {
        return node;
    }
    else if(t_root->v_time > node->v_time)
    {
        //insert at left
        t_root->left = insert_bst(t_root->left, node);
        t_root->left->parent = t_root;
    }
    else if(t_root->v_time <= node->v_time)
    {
        //insert at right
        t_root->right = insert_bst(t_root->right, node);
        t_root->right->parent = t_root;
    }
    return t_root;    
}

void RB_TREE::print_rbt(RBT_NODE *rb_root)
{
    if(rb_root == NULL)
        return;
    else
    {
        print_rbt(rb_root->left);
        cout<<rb_root->v_time<<"  "<<rb_root->p_id<<" ("<<rb_root->color<<")"<<"\t";
        print_rbt(rb_root->right);
    }
}
void RB_TREE::print_rbt_pre(RBT_NODE *rb_root)
{
    if(rb_root == NULL)
        return;
    else
    {
        cout<<rb_root->v_time<<"  "<<rb_root->p_id<<" ("<<rb_root->color<<") "<<"\t";
        print_rbt_pre(rb_root->left);
        print_rbt_pre(rb_root->right);
    }
}

void RB_TREE::left_rotate(RBT_NODE *node) 
{ 
    RBT_NODE *node_right = node->right; 
    node->right = node_right->left; 
    if (node->right != NULL) 
        node->right->parent = node; 
    node_right->parent = node->parent; 
    if (node->parent == NULL) 
        root = node_right; 
    else if (node == node->parent->left) 
        node->parent->left = node_right; 
    else
        node->parent->right = node_right; 
    node_right->left = node; 
    node->parent = node_right; 
} 
  
void RB_TREE::right_rotate(RBT_NODE *node) 
{ 
    RBT_NODE *node_left = node->left; 
    node->left = node_left->right; 
    if (node->left != NULL) 
        node->left->parent = node; 
    node_left->parent = node->parent; 
    if (node->parent == NULL) 
        root = node_left;  
    else if (node == node->parent->left) 
        node->parent->left = node_left; 
    else
        node->parent->right = node_left; 
    node_left->right = node; 
    node->parent = node_left; 
} 
void RB_TREE::check_RBT_properties(RBT_NODE *validate_process)
{
    if(validate_process->parent->color == BLACK)
    {
        return;
    }
    else if(validate_process->parent->color == RED)
    {
        RBT_NODE *parent_of_process = NULL; 
        RBT_NODE *grand_parent_of_process = NULL; 
    
        while ((validate_process != root) && (validate_process->color != BLACK) && (validate_process->parent->color == RED)) 
        { 
            parent_of_process = validate_process->parent; 
            grand_parent_of_process = validate_process->parent->parent; 

            //Parent sibling is at right
            if (parent_of_process == grand_parent_of_process->left) 
            { 
                RBT_NODE *sibling = grand_parent_of_process->right; 
                if (sibling != NULL && sibling->color == RED) 
                { 
                    grand_parent_of_process->color = RED; 
                    parent_of_process->color = BLACK; 
                    sibling->color = BLACK; 
                    validate_process = grand_parent_of_process; 
                }     
                else
                { 
                    if (validate_process == parent_of_process->right) 
                    { 
                        left_rotate(parent_of_process); 
                        validate_process = parent_of_process; 
                        parent_of_process = validate_process->parent; 
                    } 
                    right_rotate(grand_parent_of_process); 
                    int temp;
                    temp = parent_of_process->color;
                    parent_of_process->color = grand_parent_of_process->color;
                    grand_parent_of_process->color = temp;
                    validate_process = parent_of_process; 
                } 
            } 
            //parent sibling is at left
            else
            { 
                RBT_NODE *sibling = grand_parent_of_process->left; 

                if ((sibling != NULL) && (sibling->color == RED)) 
                { 
                    grand_parent_of_process->color = RED; 
                    parent_of_process->color = BLACK; 
                    sibling->color = BLACK; 
                    validate_process = grand_parent_of_process; 
                } 
                else
                { 
                    if (validate_process == parent_of_process->left) 
                    { 
                        right_rotate(parent_of_process); 
                        validate_process = parent_of_process; 
                        parent_of_process = validate_process->parent; 
                    } 
                    left_rotate(grand_parent_of_process); 
                    int temp;
                    temp = parent_of_process->color;
                    parent_of_process->color = grand_parent_of_process->color;
                    grand_parent_of_process->color = temp;
                    validate_process = parent_of_process; 
                } 
            } 
        } 
        root->color = BLACK;
    }
}
RBT_NODE* RB_TREE::search_process(RBT_NODE *tmp_root,int n)
{
    if(n==tmp_root->v_time)
        return tmp_root;
    else if(n>tmp_root->v_time)
    {
        if(tmp_root->right!=NULL)
            tmp_root = search_process(tmp_root->right, n);
    }
    else if(n<tmp_root->v_time)
    {
        if(tmp_root->left!=NULL)
            tmp_root = search_process(tmp_root->left,n);
    }
    else
        return NULL;
}

RBT_NODE* RB_TREE::find_inorder_successor(RBT_NODE *process)
{
    RBT_NODE *p_right, *in_success;
    p_right = process->right;
    in_success = inorder_successor(p_right);
    return in_success;
}
RBT_NODE* RB_TREE::inorder_successor(RBT_NODE *node)
{
    RBT_NODE *te = NULL;
    if(node != NULL)
    {
        if(node->left == NULL)
            return node;
        else
        {
            te = inorder_successor(node->left);
            return te;
        }
    }
    else   
        return te;
} 
RBT_NODE* RB_TREE::find_inorder_predecessor(RBT_NODE *process)
{
    RBT_NODE *p_left, *in_success;
    p_left = process->left;
    in_success = inorder_predecessor(p_left);
    return in_success;
}
RBT_NODE* RB_TREE::inorder_predecessor(RBT_NODE *node)
{
    RBT_NODE *te = NULL;
    if(node != NULL)
    {
        if(node->right == NULL)
            return node;
        else
        {
            te = inorder_predecessor(node->right);
            return te;
        }
    }
    else   
        return te;
}

RBT_NODE* RB_TREE::delete_process(RBT_NODE *process)
{
    //search for process
    RBT_NODE *del_process = process;
    
    if(del_process!=NULL)
    {
        if(del_process->right != NULL)
        {
            RBT_NODE *in_successor;
            in_successor = find_inorder_successor(del_process);
            del_process->v_time = in_successor->v_time;
            del_process->p_id = in_successor->p_id;
            del_process->a_time = in_successor->a_time;
            del_process->b_time = in_successor->b_time;
            del_process->nice_value = in_successor->nice_value;
            del_process->weight = in_successor->weight;
            del_process->time_slice = in_successor->time_slice;
            delete_process(in_successor);
        }
        // else if(del_process->left != NULL)
        // {
        //     RBT_NODE *in_p;
        //     in_p = find_inorder_predecessor(del_process);
        //     cout<<"\nIn predecessor = "<<in_p->v_time<<"\n";
        //     del_process->v_time = in_p->v_time;
        //     delete_process(in_p);
        // }
        else
        {
            return del_process;
        }
    }
    else
    {
        cout<<"\nProcess Not found";
    }
}
RBT_NODE* RB_TREE::right_case_3(RBT_NODE *db_right_sibling, RBT_NODE *double_black)
{
    int c_one, c_two, c_three, c_four;
    c_one = db_right_sibling->left!=NULL && db_right_sibling->left->color == BLACK && db_right_sibling->right!=NULL && db_right_sibling->right->color==BLACK;
    c_two = db_right_sibling->left!=NULL && db_right_sibling->left->color == BLACK && db_right_sibling->right==NULL;
    c_three = db_right_sibling->right==NULL && db_right_sibling->left==NULL;
    c_four = db_right_sibling->right!=NULL && db_right_sibling->right->color == BLACK && db_right_sibling->left==NULL;
    if(c_one || c_two || c_three || c_four)
    {
        if(double_black->parent->color == BLACK)
        {
            if(double_black->right==NULL)
            {
                if(double_black->parent->left == double_black)
                    double_black->parent->left = NULL;
                else if(double_black->parent->right == double_black)
                    double_black->parent->right = NULL;  
            }
            double_black = double_black->parent; 
        }
        else if(double_black->parent->color == RED)
        {
            double_black->parent->color = BLACK;
            if(double_black->parent->left == double_black)
                double_black->parent->left = NULL;
            else if(double_black->parent->right == double_black)
                double_black->parent->right = NULL;
            double_black = NULL;
        }
        db_right_sibling->color = RED;
    }
    return double_black;
}

RBT_NODE* RB_TREE::left_case_3(RBT_NODE *db_left_sibling, RBT_NODE *double_black)
{
    int c_one, c_two, c_three, c_four;
    c_one = db_left_sibling->left!=NULL && db_left_sibling->left->color == BLACK && db_left_sibling->right!=NULL && db_left_sibling->right->color==BLACK;
    c_two = db_left_sibling->left!=NULL && db_left_sibling->left->color == BLACK && db_left_sibling->right==NULL;
    c_three = db_left_sibling->right==NULL && db_left_sibling->left==NULL;
    c_four = db_left_sibling->right!=NULL && db_left_sibling->right->color == BLACK && db_left_sibling->left==NULL;
    if(c_one || c_two || c_three || c_four)
    {
        if(double_black->parent->color == BLACK)
        {
            if(double_black->right==NULL)
            {
                if(double_black->parent->left == double_black)
                    double_black->parent->left = NULL;
                else if(double_black->parent->right == double_black)
                    double_black->parent->right = NULL;  
            }
            double_black = double_black->parent; 
        }
        else if(double_black->parent->color == RED)
        {
            double_black->parent->color = BLACK;
            if(double_black->parent->left == double_black)
                double_black->parent->left = NULL;
            else if(double_black->parent->right == double_black)
                double_black->parent->right = NULL;
            double_black = NULL;
        }
        db_left_sibling->color = RED;
    }
    return double_black;
}

RBT_NODE* RB_TREE::right_case_6(RBT_NODE *db_right_sibling, RBT_NODE *double_black)
{
    int tmp_color = double_black->parent->color;
    double_black->parent->color = db_right_sibling->color;
    db_right_sibling->color = tmp_color;
    left_rotate(double_black->parent);

    db_right_sibling->right->color = BLACK;
    if(double_black->right==NULL)
    {
        if(double_black->parent->left == double_black)
            double_black->parent->left = NULL;
        else if(double_black->parent->right == double_black)
            double_black->parent->right = NULL;  
    }
    return NULL;
}

RBT_NODE* RB_TREE::left_case_6(RBT_NODE *db_left_sibling, RBT_NODE *double_black)
{
    int tmp_color = double_black->parent->color;
    double_black->parent->color = db_left_sibling->color;
    db_left_sibling->color = tmp_color;

    right_rotate(double_black->parent);

    db_left_sibling->left->color = BLACK;

    if(double_black->right==NULL)
    {
        if(double_black->parent->left == double_black)
            double_black->parent->left = NULL;
        else if(double_black->parent->right == double_black)
            double_black->parent->right = NULL;  
    }

    return NULL;
}

void RB_TREE::rbt_deletion(RBT_NODE *process)
{
    if(process == root)
    {
        // cout<<"\n del process is = "<<process->v_time;
        if(process->right==NULL)
            root = NULL;
        else
        {
            process->parent = NULL;
            root = process->right;
            root->color = BLACK;
        }
    }
    else
    {
        RBT_NODE *final_node_to_delete, *double_black;
        final_node_to_delete = delete_process(process);
        double_black = double_black_check(final_node_to_delete);
        if(double_black!=NULL)
        {
            while(double_black!=NULL)
            {
                //case 2
                if(double_black->parent == NULL)
                {
                    // cout<<"\n At case 2";
                    double_black = NULL;
                }
                else
                {            
                    // DB Sibling is at right
                    if(double_black->parent->left == double_black)
                    {
                        RBT_NODE *db_right_sibling = double_black->parent->right;
                        
                        if(db_right_sibling!=NULL)
                        {
                            if(db_right_sibling->color == BLACK)
                            {
                                //case 5
                                int c_1,c_2,c_3,c_4,c_5;
                                c_1 = db_right_sibling->left!=NULL && db_right_sibling->left->color == RED && db_right_sibling->right!=NULL && db_right_sibling->right->color == BLACK;
                                c_2 = db_right_sibling->left!=NULL && db_right_sibling->left->color == RED && db_right_sibling->right==NULL;
                                c_3 = db_right_sibling->right!=NULL && db_right_sibling->right->color == RED && db_right_sibling->left!=NULL && db_right_sibling->left->color == BLACK;
                                c_4 = db_right_sibling->right!=NULL && db_right_sibling->right->color == RED && db_right_sibling->left==NULL;
                                c_5 = db_right_sibling->right!=NULL && db_right_sibling->right->color == RED && db_right_sibling->left!=NULL && db_right_sibling->left->color == RED;
                                if(c_1 || c_2)
                                {
                                    // cout<<"\n at case 5";
                                    int tmp_color = db_right_sibling->color;
                                    db_right_sibling->color = db_right_sibling->left->color;
                                    db_right_sibling->left->color = tmp_color;
                                    
                                    //db sibling right rotate
                                    right_rotate(db_right_sibling);

                                    db_right_sibling = double_black->parent->right;
                                    
                                }
                                //case 6
                                else if(c_3||c_4||c_5)
                                {
                                    // cout<<"\n at case 6";
                                    double_black = right_case_6(db_right_sibling, double_black);
                                }
                                //case 3
                                else
                                {
                                    // cout<<"\n at case 3";
                                    double_black = right_case_3(db_right_sibling, double_black);
                                }
                            }
                            //case 4
                            else if(db_right_sibling->color == RED)
                            {
                                // cout<<"\n at case 4";
                                int tmp_color = db_right_sibling->color;
                                db_right_sibling->color = double_black->parent->color;
                                double_black->parent->color = tmp_color;
                                //parent left_rotate
                                left_rotate(double_black->parent);
                            }
                        }
                        
                    }
                    //DB Sibling is at left
                    else if(double_black->parent->right == double_black)
                    {
                        RBT_NODE *db_left_sibling = double_black->parent->left;
                        if(db_left_sibling!=NULL)
                        {
                            if(db_left_sibling->color == BLACK)
                            {
                                //case 5
                                int c_1 = db_left_sibling->right!=NULL && db_left_sibling->right->color == RED && db_left_sibling->left!=NULL && db_left_sibling->left->color == BLACK;
                                int c_2 = db_left_sibling->right!=NULL && db_left_sibling->right->color == RED && db_left_sibling->left==NULL;
                                int c_3 = db_left_sibling->left!=NULL && db_left_sibling->left->color == RED && db_left_sibling->right!=NULL && db_left_sibling->right->color == BLACK;
                                int c_4 = db_left_sibling->left!=NULL && db_left_sibling->left->color == RED && db_left_sibling->right==NULL;
                                int c_5 = c_5 = db_left_sibling->right!=NULL && db_left_sibling->right->color == RED && db_left_sibling->left!=NULL && db_left_sibling->left->color == RED;
                                if(c_1 || c_2)
                                {
                                    // cout<<"\n left at case 5";
                                    int tmp_color = db_left_sibling->color;
                                    db_left_sibling->color = db_left_sibling->right->color;
                                    db_left_sibling->right->color =tmp_color;
                                    //db sibling left rotate
                                    left_rotate(db_left_sibling);
                                    db_left_sibling = double_black->parent->left;
                                }
                                //case 6
                                else if(c_3||c_4||c_5)
                                {
                                    // cout<<"\n left at case 6";
                                    double_black = left_case_6(db_left_sibling, double_black);
                                }
                                //case 3
                                else
                                {
                                    // cout<<"\n left at case 3";
                                    double_black = left_case_3(db_left_sibling, double_black);
                                }
                            }
                            //case 4
                            else if(db_left_sibling->color == RED)
                            {   
                                // cout<<"\n left at case 4";                             
                                int tmp_color = db_left_sibling->color;
                                db_left_sibling->color = double_black->parent->color;
                                double_black->parent->color = tmp_color;
                                //parent right_rotate
                                right_rotate(double_black->parent);
                            }
                        }
                    }
                }
            }
            free(double_black);
        }
        // else
        //     cout<<"\nNO Double Black Problem";
    }
}

RBT_NODE* RB_TREE::find_min(RBT_NODE *t_root)
{
    RBT_NODE *tmp_root = t_root;
    while(tmp_root->left!=NULL)
    {
        tmp_root = tmp_root->left;
    }
    return tmp_root;
}

RBT_NODE* RB_TREE::get_min_vtime_process(RBT_NODE *t_root)
{
    RBT_NODE *min, *tmp;
    RBT_NODE *min2 = new RBT_NODE();
    min = find_min(t_root);
    min2->v_time = min->v_time;
    min2->b_time = min->b_time;
    min2->p_id = min->p_id;
    min2->a_time = min->a_time;
    min2->nice_value = min->nice_value;
    min2->weight = min->weight;
    min2->time_slice = min->time_slice;
    tmp = min;
    rbt_deletion(tmp);
    return min2;
}

int* RB_TREE::gaussiandistribution(int n, int mean, int stdev)
{

    default_random_engine generator;
    normal_distribution<double> distribution(mean,stdev);

    int* p= new int[n];
    int i=0;
    while(1){
        int number = distribution(generator);
        if(number>9&&number<201)
        {
            p[i]=number;
            i++;
            if(i==n)
                return p;
        }
    }
}
