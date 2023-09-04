/**
 * Linked LIst Library
 * 
 * @file: llist.c
 * @author: Elena Vedaleva
 * @date: September, 2023
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "llist.h"

/**
 * Merges two sorted lists (lowers to higherst) 
 * into a single sorted list.
 * 
 * @param: pointer to head of the first list
 * @param: pointer to head of the second list
 * @return: pointer to head of the mearged list
*/
Node *merge_sorted_lists(Node *list1, Node *list2) {
    if (!list1) return list2;
    if (!list2) return list1;

    Node *head = NULL;
    Node *previous_node = NULL;
    if (list1->value < list2->value) {
        head = list1;
        list1 = list1->next;
    } else {
        head = list2;
        list2 = list2->next;
    }
    previous_node = head;

    while (list1 && list2) {
        if (list1->value < list2->value) {
            previous_node->next = list1;
            previous_node = previous_node->next;
            list1 = list1->next;
        } else {
            previous_node->next = list2;
            previous_node = previous_node->next;
            list2 = list2->next;
        } 
    }
    if (list1) previous_node->next = list1;
    if (list2) previous_node->next = list2;
    
    return head;
}

Node *add_lists(Node *list1, Node *list2) {
    if (!list1 || !list2) return NULL;

    Node *cur1 = list1;
    Node *cur2 = list2;
    while (cur1 && cur2) {
        cur1->value += cur2->value;
        cur1 = cur1->next;
        cur2 = cur2->next; 
    }

    return list1;
}

Node *duplicate_list(Node *node) {
    if (!node) return NULL;

    Node *new_node = (Node*)calloc(1, sizeof(Node));
    new_node->value = node->value;

    new_node->next = duplicate_list(node->next);

    return new_node;
}

Node *insert_at_head(Node *head, int new_value) {
	Node *new_node = calloc(1, sizeof(Node));
	if (new_node == NULL) {
		perror("calloc");
		exit(1);
	}
	
	new_node->value = new_value;
	if (head != NULL) {
		new_node->next = head;
	}

	return new_node;
}

Node *insert_at_tail(Node *head, int new_value) {
	Node *new_node = calloc(1, sizeof(Node));
	if (new_node == NULL) {
		perror("calloc");
		exit(1);
	}

	new_node->value = new_value;
	if (head == NULL) return new_node;

	Node *current = head;
	while (current->next != NULL) current = current->next;
	current->next = new_node;
	return head;
}

Node *delete_at_head(Node *head) {
	if (head == NULL) return NULL;

	Node *new_head = head->next;
	free(head);
	return new_head;
}

Node *delete_at_tail(Node *head) {
	if (head == NULL) return NULL;
	
	Node *before_current = head;
	Node *current = head->next;
	if (current == NULL) {
		free(before_current);
		return NULL;
	}
	while (current->next != NULL) {
		before_current = current;
		current = current->next;
	}
	before_current->next = NULL;
	free(current);
	
	return head;
}

void print_list(Node *head) {
	Node *current;
	current = head;
	int i = 0;
	for (; current; current = current->next) {         
		printf("Node %d value: %d\n", i, current->value);   
		i++;
	}	
}

int length(Node *head) {
	Node *current = head;
	int length = 0;
	while (current != NULL) {
		current = current->next;
		length++;
	}
	return length;
}

int recursive_length(Node *node) {
	if (node == NULL) return 0;
	
	return 1 + recursive_length(node->next);
}

bool is_member(Node *node, int find_value) {
	if (node == NULL) return false;

	if (node->value == find_value) return true;
	else return is_member(node->next, find_value);
}

int count_matches(Node *node, int count_value) {
	if (node == NULL) return 0;

	if (node->value == count_value) {
		return 1 + count_matches(node->next, count_value);
	} else return count_matches(node->next, count_value);
}

void replace_matches(Node *node, int find_value, int replace_value) {
	if (node != NULL) {
		if (node->value == find_value) node->value = replace_value;
		replace_matches(node->next, find_value, replace_value);
	}
}

Node *delete_first_match(Node *head, int delete_value, bool *was_deleted) {
	if (head && head->value == delete_value) {
		*was_deleted = true;
		Node *new_head = head->next;
		free(head);
		return new_head;
	}

	Node *previous_current = head;
	Node *current = head->next;
	while (current != NULL) {
		if (current->value == delete_value) {
			previous_current->next = current->next;
			*was_deleted = true;
			free(current);
			return head;
		}
		previous_current = current;
		current = current->next;
	}

	*was_deleted = false;
	return head;
}

Node *delete_all_matches(Node *head, int delete_value, int *num_deleted) {
	*num_deleted = 0;
	bool was_deleted;
	while (true) {
		head = delete_first_match(head, delete_value, &was_deleted);

		if (was_deleted) (*num_deleted)++;
		else break;
	}
	return head;
}

Node *delete_all_matches2(Node *head, int delete_value, int *num_deleted) {
	*num_deleted = 0;

	while (head && head->value == delete_value) {
		Node *new_head = head->next;
		free(head);
		head = new_head;
		(*num_deleted)++;
	}

	if (head == NULL) return head;

	Node *previous_current = head;
	Node *current = head->next;
	while (current != NULL) {
		if (current->value == delete_value) {
			previous_current->next = current->next;
			free(current);
			current = previous_current->next;
			(*num_deleted)++;
		} else {
			previous_current = current;
			current = current->next;
		}
	}

	return head;
}

Node *append_list(Node *head1, Node *head2) {
	if (head1 == NULL) return head2;

	Node *current = head1;
	while (current->next != NULL) current = current->next;
	current->next = head2;

	return head1;
}

Node *reverse_list(Node *head) {
	if (head == NULL || head->next == NULL) return head;

	Node *previous_current = NULL;
	Node *current = head;
	while (current != NULL) {
		Node *tmp = previous_current;  
		previous_current = current;     
		current = current->next;        
		previous_current->next = tmp;  
	}

	return previous_current;
}

void bubble_sort_list(Node *head) {
	if (!head || !head->next) return;

	bool is_swapped = false;
	
	for (Node *i_node = head; i_node; i_node = i_node->next) {
		for (Node *j_node = i_node; j_node->next; j_node = j_node->next) {
			if (j_node->value > j_node->next->value) {
				int tmp = j_node->value;
				j_node->value = j_node->next->value;
				j_node->next->value = tmp;
				is_swapped = true;
			}		
		}
		if (!is_swapped) break;
	}
}

void delete_duplicates(Node *head) {
	if (!head || !head->next) return;
	
	Node *node = head;
	Node *previous, *current;
	while (node) {
		previous = node;
	    current = node->next;
		while (current) {
			if (node->value == current->value) {
				previous->next = current->next;
				free(current);
				current = previous->next;
				continue;
			}
			previous = current;
			current= current->next;		
		}
		node = node->next;
	}
}

Node *insert_after(Node *head, int insert_value, int after_value) {
	Node *new = calloc(1, sizeof(Node));
	new->value = insert_value;

	if (!head) return new;
	
	Node *current = head;
	while (current->next) {
		if (current->value == after_value) {
			new->next = current->next;
			current->next = new;
			return head;
		}
		current = current->next;
	}

	current->next = new;
	return head;
}

Node *delete_list(Node *node) {
	if (!node) return NULL;

	Node *next_node;
	while (node) {
		next_node = node->next;
		free(node);
		node = next_node;
	}

	return NULL;
}