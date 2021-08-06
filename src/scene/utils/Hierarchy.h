#ifndef RPG_HIERARCHY_H
#define RPG_HIERARCHY_H

#include "../Entity.h"

/**
 * Утилитный класс для работы с иерархией энтити.
 */
class Hierarchy
{
public:
    /**
     * Добавить к энтити нового ребенка.
     *
     * @param parent родитель
     * @param child ребенок
     */
    static void addChild(Entity parent, Entity child);

    /**
     * Найти дочерний энтити по имени.
     *
     * @param parent родитель
     * @param name имя энтити
     * @return найденный или пустой энтити
     */
    static Entity find(Entity parent, std::string name);

    /**
     * Вычислить трансформации с учетом иерархии.
     *
     * @param entity энтити
     * @return трансформации с учетом иерархии
     */
    static TransformComponent computeTransform(Entity entity);
};


#endif //RPG_HIERARCHY_H
