#ifndef MAP_H
#define MAP_H

#include "entity.h"
#include "entityCollection.h"
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>

/**
 * This class controls the visual world space in which the user is able to interact.
*/
class Map {
    public: 
        EntityCollection collection = EntityCollection();

        // Utilities:
        void generateSpace(std::size_t p_col, std::size_t p_row) {
            std::vector<std::vector<char>> l_space(p_col, std::vector<char>(p_row, collection.m_grass.getSprite()));

            setSpace(l_space);
        }

        /**
         * Modifies the [m_space] at coordinates [p_col][p_row]. 
         * Takes in an [Entity] to derive its visual sprite for placement in the map
         * and its name for key value storage in [m_positions]
        */
        void modifySpace(std::size_t p_col, std::size_t p_row) {
            std::size_t entityColPos = getPostion().first;
            std::size_t entityRowPos = getPostion().second;
            std::size_t newColPos = entityColPos + p_col;
            std::size_t newRowPos = entityRowPos + p_row; 

            // TODO: Modify method to take in replacement sprite.
            m_space[entityColPos][entityRowPos] = collection.m_grass.getSprite();

            m_space[newColPos][newRowPos] = m_operatingEntity.getSprite();
            m_positions[m_operatingEntity.getName()] = std::pair<std::size_t, std::size_t> { newColPos, newRowPos };
        }

        /**
         * Iterates through the 2D [m_space] vector and prints it to the screen.
        */
        void printSpace() {
            for (decltype(m_space)::size_type col = 0; col < m_space.size(); col++) {
                for (decltype(m_space)::size_type row = 0; row < m_space[col].size(); row++) {
                    std::cout << "\x1B[32m" << m_space[col][row]; 
                }
                std::cout << "\n";
            } 
        }

        // Getters:
        std::pair<std::size_t, std::size_t> getPostion() { return m_positions[m_operatingEntity.getName()]; }
        Entity getOperatingEntity() { return m_operatingEntity; }

        // Setters:
        void setSpace(std::vector<std::vector<char>> p_space) { m_space = p_space; }
        void setOperatingEntity(Entity p_entity) { m_operatingEntity = p_entity; }

    private:
        Entity m_operatingEntity;
        std::vector<std::vector<char>> m_space;
        std::unordered_map<std::string, std::pair<std::size_t, std::size_t>> m_positions;
};

#endif