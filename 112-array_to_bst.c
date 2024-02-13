
100-binary_trees_ancestor.c


#include "binary_trees.h"


/**

 * binary_trees_ancestor - Finds the lowest common ancestor of two nodes.

 * @first: Pointer to the first node.

 * @second: Pointer to the second node.

 *

 * Return: If no common ancestors return NULL, else return common ancestor.

 */

binary_tree_t *binary_trees_ancestor(const binary_tree_t *first,

                const binary_tree_t *second)

{

        binary_tree_t *mom, *pop;


        if (!first || !second)

                return (NULL);

        if (first == second)

                return ((binary_tree_t *)first);


        mom = first->parent, pop = second->parent;

        if (first == pop || !mom || (!mom->parent && pop))

                return (binary_trees_ancestor(first, pop));

        else if (mom == second || !pop || (!pop->parent && mom))

                return (binary_trees_ancestor(mom, second));

        return (binary_trees_ancestor(mom, pop));

}


101-binary_tree_levelorder.c


#include "binary_trees.h"


levelorder_queue_t *create_node(binary_tree_t *node);

void free_queue(levelorder_queue_t *head);

void pint_push(binary_tree_t *node, levelorder_queue_t *head,

                levelorder_queue_t **tail, void (*func)(int));

void pop(levelorder_queue_t **head);

void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int));


/**

 * create_node - Creates a new levelorder_queue_t node.

 * @node: The binary tree node for the new node to contain.

 *

 * Return: If an error occurs, NULL.

 *         Otherwise, a pointer to the new node.

 */

levelorder_queue_t *create_node(binary_tree_t *node)

{

        levelorder_queue_t *new;


        new = malloc(sizeof(levelorder_queue_t));

        if (new == NULL)

                return (NULL);


        new->node = node;

        new->next = NULL;


        return (new);

}


/**

 * free_queue - Frees a levelorder_queue_t queue.

 * @head: A pointer to the head of the queue.

 */

void free_queue(levelorder_queue_t *head)

{

        levelorder_queue_t *tmp;


        while (head != NULL)

        {

                tmp = head->next;

                free(head);

                head = tmp;

        }

}


/**

 * pint_push - Runs a function on a given binary tree node and

 *             pushes its children into a levelorder_queue_t queue.

 * @node: The binary tree node to print and push.

 * @head: A double pointer to the head of the queue.

 * @tail: A double pointer to the tail of the queue.

 * @func: A pointer to the function to call on @node.

 *

 * Description: Upon malloc failure, exits with a status code of 1.

 */

void pint_push(binary_tree_t *node, levelorder_queue_t *head,

                levelorder_queue_t **tail, void (*func)(int))

{

        levelorder_queue_t *new;


        func(node->n);

        if (node->left != NULL)

        {

                new = create_node(node->left);

                if (new == NULL)

                {

                        free_queue(head);

                        exit(1);

                }

                (*tail)->next = new;

                *tail = new;

        }

        if (node->right != NULL)

        {

                new = create_node(node->right);

                if (new == NULL)

                {

                        free_queue(head);

                        exit(1);

                }

                (*tail)->next = new;

                *tail = new;

        }

}


/**

 * pop - Pops the head of a levelorder_queue_t queue.

 * @head: A double pointer to the head of the queue.

 */

void pop(levelorder_queue_t **head)

{

        levelorder_queue_t *tmp;


        tmp = (*head)->next;

        free(*head);

        *head = tmp;

}


/**

 * binary_tree_levelorder - Traverses a binary tree using

 *                          level-order traversal.

 * @tree: A pointer to the root node of the tree to traverse.

 * @func: A pointer to a function to call for each node.

 */

void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))

{

        levelorder_queue_t *head, *tail;


        if (tree == NULL || func == NULL)

                return;


        head = tail = create_node((binary_tree_t *)tree);

        if (head == NULL)

                return;


        while (head != NULL)

        {

                pint_push(head->node, head, &tail, func);

                pop(&head);

        }

}


102-binary_tree_is_complete.c


#include "binary_trees.h"


levelorder_queue_t *create_node(binary_tree_t *node);

void free_queue(levelorder_queue_t *head);

void push(binary_tree_t *node, levelorder_queue_t *head,

                levelorder_queue_t **tail);

void pop(levelorder_queue_t **head);

int binary_tree_is_complete(const binary_tree_t *tree);


/**

 * create_node - Creates a new levelorder_queue_t node.

 * @node: The binary tree node for the new node to contain.

 *

 * Return: If an error occurs, NULL.

 *         Otherwise, a pointer to the new node.

 */

levelorder_queue_t *create_node(binary_tree_t *node)

{

        levelorder_queue_t *new;


        new = malloc(sizeof(levelorder_queue_t));

        if (new == NULL)

                return (NULL);


        new->node = node;

        new->next = NULL;


        return (new);

}


/**

 * free_queue - Frees a levelorder_queue_t queue.

 * @head: A pointer to the head of the queue.

 */

void free_queue(levelorder_queue_t *head)

{

        levelorder_queue_t *tmp;


        while (head != NULL)

        {

                tmp = head->next;

                free(head);

                head = tmp;

        }

}


/**

 * push - Pushes a node to the back of a levelorder_queue_t queue.

 * @node: The binary tree node to print and push.

 * @head: A double pointer to the head of the queue.

 * @tail: A double pointer to the tail of the queue.

 *

 * Description: Upon malloc failure, exits with a status code of 1.

 */

void push(binary_tree_t *node, levelorder_queue_t *head,

                levelorder_queue_t **tail)

{

        levelorder_queue_t *new;


        new = create_node(node);

        if (new == NULL)

        {

                free_queue(head);

                exit(1);

        }

        (*tail)->next = new;

        *tail = new;

}


/**

 * pop - Pops the head of a levelorder_queue_t queue.

 * @head: A double pointer to the head of the queue.

 */

void pop(levelorder_queue_t **head)

{

        levelorder_queue_t *tmp;


        tmp = (*head)->next;

        free(*head);

        *head = tmp;

}


/**

 * binary_tree_is_complete - Checks if a binary tree is complete.

 * @tree: A pointer to the root node of the tree to traverse.

 *

 * Return: If the tree is NULL or not complete, 0.

 *         Otherwise, 1.

 *

 * Description: Upon malloc failure, exits with a status code of 1.

 */

int binary_tree_is_complete(const binary_tree_t *tree)

{

        levelorder_queue_t *head, *tail;

        unsigned char flag = 0;


        if (tree == NULL)

                return (0);


        head = tail = create_node((binary_tree_t *)tree);

        if (head == NULL)

                exit(1);


        while (head != NULL)

        {

                if (head->node->left != NULL)

                {

                        if (flag == 1)

                        {

                                free_queue(head);

                                return (0);

                        }

                        push(head->node->left, head, &tail);

                }

                else

                        flag = 1;

                if (head->node->right != NULL)

                {

                        if (flag == 1)

                        {

                                free_queue(head);

                                return (0);

                        }

                        push(head->node->right, head, &tail);

                }

                else

                        flag = 1;

                pop(&head);

        }

        return (1);

}


103-binary_tree_rotate_left.c


#include "binary_trees.h"


/**

 * binary_tree_rotate_left - Left-rotates a binary tree.

 * @tree: A pointer to the root node of the tree to rotate.

 *

 * Return: A pointer to the new root node after rotation.

 */

binary_tree_t *binary_tree_rotate_left(binary_tree_t *tree)

{

        binary_tree_t *pivot, *tmp;


        if (tree == NULL || tree->right == NULL)

                return (NULL);


        pivot = tree->right;

        tmp = pivot->left;

        pivot->left = tree;

        tree->right = tmp;

        if (tmp != NULL)

                tmp->parent = tree;

        tmp = tree->parent;

        tree->parent = pivot;

        pivot->parent = tmp;

        if (tmp != NULL)

        {

                if (tmp->left == tree)

                        tmp->left = pivot;

                else

                        tmp->right = pivot;

        }


        return (pivot);

}


104-binary_tree_rotate_right.c


#include "binary_trees.h"


/**

 * binary_tree_rotate_right - Right-rotates a binary tree.

 * @tree: A pointer to the root node of the tree to rotate.

 *

 * Return: A pointer to the new root node after rotation.

 */

binary_tree_t *binary_tree_rotate_right(binary_tree_t *tree)

{

        binary_tree_t *driver, *tmp;


        if (tree == NULL || tree->left == NULL)

                return (NULL);


        driver = tree->left;

        tmp = driver->right;

        driver->right = tree;

        tree->left = tmp;

        if (tmp != NULL)

                tmp->parent = tree;

        tmp = tree->parent;

        tree->parent = driver;

        driver->parent = tmp;

        if (tmp != NULL)

        {

                if (tmp->left == tree)

                        tmp->left = driver;

                else

                        tmp->right = driver;

        }


        return (driver);

}


110-binary_tree_is_bst.c


#include "binary_trees.h"

#include "limits.h"


/**

 * is_bst_helper - Checks if a binary tree is a valid binary search tree.

 * @tree: A pointer to the root node of the tree to check.

 * @lo: The value of the smallest node visited thus far.

 * @hi: The value of the largest node visited this far.

 *

 * Return: If the tree is a valid BST, 1, otherwise, 0.

 */

int is_bst_helper(const binary_tree_t *tree, int lo, int hi)

{

        if (tree != NULL)

        {

                if (tree->n < lo || tree->n > hi)

                        return (0);

                return (is_bst_helper(tree->left, lo, tree->n - 1) &&

                        is_bst_helper(tree->right, tree->n + 1, hi));

        }

        return (1);

}


/**

 * binary_tree_is_bst - Checks if a binary tree is a valid binary search tree.

 * @tree: A pointer to the root node of the tree to check.

 *

 * Return: 1 if tree is a valid BST, and 0 otherwise

 */

int binary_tree_is_bst(const binary_tree_t *tree)

{

        if (tree == NULL)

                return (0);

        return (is_bst_helper(tree, INT_MIN, INT_MAX));

}


111-bst_insert.c


#include "binary_trees.h"


/**

 * bst_insert - Inserts a value in a Binary Search Tree.

 * @tree: A double pointer to the root node of the BST to insert the value.

 * @value: The value to store in the node to be inserted.

 *

 * Return: A pointer to the created node, or NULL on failure.

 */

bst_t *bst_insert(bst_t **tree, int value)

{

        bst_t *curr, *new;


        if (tree != NULL)

        {

                curr = *tree;


                if (curr == NULL)

                {

                        new = binary_tree_node(curr, value);

                        if (new == NULL)

                                return (NULL);

                        return (*tree = new);

                }


                if (value < curr->n) /* insert in left subtree */

                {

                        if (curr->left != NULL)

                                return (bst_insert(&curr->left, value));


                        new = binary_tree_node(curr, value);

                        if (new == NULL)

                                return (NULL);

                        return (curr->left = new);

                }

                if (value > curr->n) /* insert in right subtree */

                {

                        if (curr->right != NULL)

                                return (bst_insert(&curr->right, value));


                        new = binary_tree_node(curr, value);

                        if (new == NULL)

                                return (NULL);

                        return (curr->right = new);

                }

        }

        return (NULL);

}


112-array_to_bst.c


#include "binary_trees.h"


/**

 * array_to_bst - Builds a binary search tree from an array.

 * @array: A pointer to the first element of the array to be converted.

 * @size: The number of elements in @array.

 *

 * Return: A pointer to the root node of the created BST, or NULL upon failure.

 */

bst_t *array_to_bst(int *array, size_t size)

{

        bst_t *tree = NULL;

        size_t i, j;


        if (array == NULL)

                return (NULL);


        for (i = 0; i < size; i++)

        {

                for (j = 0; j < i; j++)

                {

                        if (array[j] == array[i])

                                break;

                }

                if (j == i)

                {

                        if (bst_insert(&tree, array[i]) == NULL)

                                return (NULL);

                }

        }


        return (tree);

}
