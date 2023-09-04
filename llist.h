/**
 * Linked List Library
 * 
 * @file: llist.h
 * @author: Elena Vedaleva
 * @date: September, 2023
 * 
*/
#include <stdbool.h>

/**
 * A node in a linked list
 * 
*/
typedef struct node {
	int value; /**< the value stored in the node */
	struct node *next; /**< pointer to the next node in the list */
} Node;

Node *insert_at_head(Node *head, int new_value);
Node *insert_at_tail(Node *head, int new_value);
Node *delete_at_head(Node *head);
Node *delete_at_tail(Node *head);
void print_list(Node *head);
int length(Node *head);
int recursive_length(Node *head);
bool is_member(Node *node, int find_value);
int count_matches(Node *node, int count_value);
void replace_matches(Node *node, int find_value, int replace_value);
Node *delete_first_match(Node *head, int delete_value, bool *was_deleted);
Node *delete_all_matches(Node *head, int delete_value, int *num_deleted);
Node *delete_all_matches2(Node *head, int delete_value, int *num_deleted);
Node *append_list(Node *head1, Node *head2);
Node *reverse_list(Node *head);
void bubble_sort_list(Node *head);
void delete_duplicates(Node *head);
Node *insert_after(Node *head, int insert_value, int after_value); 
Node *delete_list(Node *node);
Node *add_lists(Node *list1, Node *list2);
Node *duplicate_list(Node *src_list);
Node *merge_sorted_lists(Node *list1, Node *list2);