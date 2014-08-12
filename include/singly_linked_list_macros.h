/**
 * \brief Get offset of a member
 * \param type Type of struct
 * \param member Name of member of struct
 * \return The offset of the member in the struct
 */
#define offsetof(type, member) ((size_t) &((type *)0)->member)

/**
 * \brief Gives pointer to "container-struct"
 * \param ptr The pointer to the member.
 * \param type The type of the container struct this is embedded in.
 * \param member The name of the member within the struct.
 */
#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

/** \brief Return the last entry of the list
 * \param head The head of the list
 * \return Last entry of the list
 */
#define S_LAST_ENTRY(head) S_BEFORE_ENTRY((head), NULL)

/**
 * \brief Singly-Linked-List Macro expands to entry before "entry"
 * \param head The head of the list
 * \param entry The Successor of the wanted entry
 * \return
 * NULL if predecessor of entry was not found
 * Predecessor of entry if it was found
 */
#define S_BEFORE_ENTRY(head, entry) ({					\
	typeof(head) __last = head;					\
	typeof(head) __prev = head;					\
									\
	while (__last) {						\
		__prev = __last;					\
		__last = __last->next;					\
		if (__last == (entry))					\
			break;						\
	}								\
	__prev;								\
})

/**
 * \brief Singly-Linked-List Macro deletes "entry" from list
 *
 * NOTICE: You need a pointer to the _real_ head! (enclosing container)
 * A pointer only _containing_ the address of the head will not work properly!
 * Because container_of-Macro is used
 *
 * \param head The head of the list
 * \param entry The entry we want to delete
 */
#define S_DELETE_ENTRY(head, entry) ({					\
	typeof(head) __help = container_of(&head, typeof(*head), next); \
	typeof(head) __before = S_BEFORE_ENTRY(__help, entry);		\
	typeof(head) __save = NULL;					\
									\
	if (__before && (entry)) {					\
		__save = (entry)->next;					\
		free(__before->next);					\
		__before->next = __save;				\
	}								\
})

/**
 * \brief Singly-Linked-List Macro deletes list
 *
 * NOTICE: You need a pointer to the _real_ head! (enclosing container)
 * A pointer only _containing_ the address of the head will not work properly!
 * Because container_of-Macro is used
 *
 * \param head The head of the list
 */
#define S_DELETE_LIST(head) ({						\
	while (head)							\
		S_DELETE_ENTRY(head, head);				\
})

/**
 * \brief Iterate over list conveniently
 * \param head The head of the list
 * \param iter Given iteration-variable (must been declared outside of macro)
 */
#define S_FOR_EACH_ENTRY(head, iter)	 				\
	for (iter = (head); (iter); iter = (iter)->next)
