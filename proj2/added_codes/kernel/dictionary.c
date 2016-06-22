#include <linux/unistd.h>
#include <linux/linkage.h>

#include <linux/bug.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

/// default supported dictionary size
#define DICT_S 0x400

char* dict[DICT_S] = {NULL};  // hash table of dict. w/ size DICT_S
int   s[DICT_S]    = {0};     // size of each dict.

/** Estimate array index by a hash function of size DICT_S
 *    return: index of hash table
 **/
int hash(int key) {
    int hash = key;

    /* hash function taken from http://stackoverflow.com/a/12996028 */
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = ((hash >> 16) ^ hash);

    return hash % DICT_S;
}

/** Get a value from a specified key 
  *   key:   id of the desired value
  *   value: ptr for the final value
  **/
asmlinkage long sys_getkey(int key, char __user *value) 
{
    int    error,
           id = hash(key);

    /* Tries to copy data to user */
    error = -EFAULT;
    if (copy_to_user(value, dict[id], s[id] * sizeof(char))) {
        goto out;
    }

    /* Success */ 
    return 0;

out:
    return error;
}

/** Set specified key with the given value
  *   key:   id of the value
  *   value: desirede value to be stored
  *   n:     size of the value 
  **/
asmlinkage long sys_setkey(int key, const char __user *value, int n) 
{
    int    error,
           id = hash(key);

    /* Set memory and size */
    dict[id] = kmalloc(n, GFP_KERNEL);
    s[id]    = n;

    /* Tries to copy data from user */
    error = -EFAULT;
    if (copy_from_user(dict[id], value, n * sizeof(char))) {
        /* Revert changes and go away! */
        kfree(dict[hash(key)]);
        s[id] = 0;

        goto out;
    }

    /* Success */
    return 0;

out:
    return error;
}
