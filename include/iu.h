/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** iu
*/

#ifndef IU_H_
    #define IU_H_

void iu_init(demo_t *demo);
void set_entities(void);

rect_t entity_get_size(entity2_t entity);
void iu_display(void);

void iu_entity_draw(entity2_t entity);

void iu_quit(void);
#endif /* !IU_H_ */
