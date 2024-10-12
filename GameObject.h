#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class GameObject {
public:
    virtual ~GameObject() = default;

    // Metodi virtuali puri che devono essere implementati dalle classi derivate
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;

    // Per la gestione delle collisioni
    virtual sf::FloatRect getBounds() const = 0;
    virtual sf::Vector2f getPosition() const = 0;

    // Tipo dell'oggetto, per identificare la classe derivata
    enum class ObjectType {
        Player,
        Bullet,
        Asteroid,
        // Puoi aggiungere altri tipi se necessario
    };

    virtual ObjectType getType() const = 0;

    // Gestione dello stato attivo/inattivo dell'oggetto
    void setActive(bool active) { this->active = active; }
    bool isActive() const { return active; }

    // Per raccogliere nuovi oggetti creati durante l'update (ad esempio, proiettili)
    virtual std::vector<std::unique_ptr<GameObject>> collectNewObjects()
    {
        return {};
    }

protected:
    bool active = true; // Stato attivo dell'oggetto
};
