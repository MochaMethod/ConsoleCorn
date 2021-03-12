#ifndef MAP_H
#define MAP_H

#include "entity.h"
#include "entityCollection.h"
#include "uiController.h"
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <random>

/**
 * This class controls the visual world space in which the user is able to interact.
*/
class Map {
    public: 
        EntityCollection collection = EntityCollection();

        // Utilities:
        void generateSpace(std::pair<std::size_t, std::size_t> p_spaceBounds) {
            std::vector<std::vector<char>> space(p_spaceBounds.first, std::vector<char>(p_spaceBounds.second, collection.m_grass.getSprite()));

            int cornAmt = 10;

            for (int index = 0; index < cornAmt; index++) {
                std::pair<std::size_t, std::size_t> cornPosition = { 3, 5 };
                int moveColAmount = rand() % cornAmt + 1;
                int moveRowAmount = rand() % cornAmt + 1;
                cornPosition.first += moveColAmount;
                cornPosition.second += moveRowAmount;
                space[cornPosition.first][cornPosition.second] = collection.m_corn.getSprite();
            }
            
            setSpaceBounds(p_spaceBounds);
            setSpace(space);
        }

        std::pair<std::size_t, std::size_t> getUpdatedPosition(std::pair<std::size_t, std::size_t> p_position) {
            std::size_t entityColPos = getOperatingEntityPosition().first;
            std::size_t entityRowPos = getOperatingEntityPosition().second;
            std::size_t newColPos = entityColPos + p_position.first;
            std::size_t newRowPos = entityRowPos + p_position.second;
            return std::pair<std::size_t, std::size_t> { newColPos, newRowPos };
        }

        /**
         * Modifies the [m_space] at coordinates [p_col][p_row]. 
         * Takes in an [Entity] to derive its visual sprite for placement in the map
         * and its name for key value storage in [m_positions]
        */
        void modifySpace(std::pair<std::size_t, std::size_t> p_newPosition) {
            // TODO: Modify method to take in replacement sprite.

            // Get old position and set it to another sprite. Then update the position with the new position.
            m_space[getOperatingEntityPosition().first][getOperatingEntityPosition().second] = getStandingOnEntitySprite();

            setStandingOnEntitySprite(m_space[p_newPosition.first][p_newPosition.second]);
            setOperatingEntityPosition(p_newPosition);
            
            m_space[p_newPosition.first][p_newPosition.second] = m_operatingEntity.getSprite();
        }

        /**
         * Iterates through the 2D [m_space] vector and prints it to the screen.
        */
        void printSpace() {
            // TODO: Handle color codes.
            for (decltype(m_space)::size_type col = 0; col < m_space.size(); col++) {
                for (decltype(m_space)::size_type row = 0; row < m_space[col].size(); row++) {
                    std::cout << m_space[col][row]; 
                }
                std::cout << "\n";
            } 
        }

        bool willCollideWithBorder(std::pair<std::size_t, std::size_t> p_position) {
            std::size_t colUpperBounds = m_spaceBounds.first;
            std::size_t rowUpperBounds = m_spaceBounds.second;
            std::size_t lowerBounds = -1;
            bool isColUpperBounds = p_position.first == colUpperBounds;
            bool isRowUpperBounds = p_position.second == rowUpperBounds;
            bool isColLowerBounds = p_position.first == lowerBounds;
            bool isRowLowerBounds = p_position.second == lowerBounds;

            if (isColUpperBounds || isColLowerBounds) {
                return true;
            } 
            
            if (isRowUpperBounds || isRowLowerBounds) {
                return true;
            }

            return false;
        }

        void handleInteraction() {
            if (m_standingOnEntitySprite == '!') {
                std::cout << "Corn!" << std::endl;
            } 
        }

        // Getters:
        std::pair<std::size_t, std::size_t> getOperatingEntityPosition() { return m_positions[m_operatingEntity.getName()]; }
        Entity getOperatingEntity() { return m_operatingEntity; }
        char getStandingOnEntitySprite() { return m_standingOnEntitySprite; }

        // Setters:
        void setSpace(std::vector<std::vector<char>> p_space) { m_space = p_space; }
        void setOperatingEntity(Entity p_entity) { m_operatingEntity = p_entity; }
        void setSpaceBounds(std::pair<std::size_t, std::size_t> p_spaceBounds) { m_spaceBounds = p_spaceBounds; }
        void setOperatingEntityPosition(std::pair<std::size_t, std::size_t> p_position) { 
            m_positions[m_operatingEntity.getName()] = p_position;
        }
        void setStandingOnEntitySprite(char p_sprite) { m_standingOnEntitySprite = p_sprite; }

    private:
        Entity m_operatingEntity;
        std::vector<std::vector<char>> m_space;
        std::unordered_map<std::string, std::pair<std::size_t, std::size_t>> m_positions;
        char m_standingOnEntitySprite;
        std::pair<std::size_t, std::size_t> m_spaceBounds;
};

#endif