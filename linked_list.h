struct Address* create_node(char *name, char *surname, char *email, char *phone);
void get_all_nodes(struct Address **pnt);
void add_node_to_list(struct Address **pnt, struct Address *address);
void add_node_to_position(struct Address **pnt, struct Address *address, int index);
void remove_one_node(struct Address **pnt, int index);
void remove_all_nodes(struct Address **pnt);
void find_node_by_position(struct Address **pnt, int index);
void find_node_by_attribute(struct Address **pnt, char attribute[], char value[]);
