#ifndef TEXT_HPP
#define TEXT_HPP

#include "model/entity.hpp"

/* A text entity is a bloc of text on the grid. For example the blocs for BABA,
WIN, IS... These blocs always have the property PUSH. */
class TextEntity: public Entity {
  public:
    bool hasProp(const Property &p) const override;
    void addProp(const Property &p) override;
    void clearProp() override;
    const std::set<const Property*> getProp() const override;

  protected:
    TextEntity() = default;

  private:
    // !! All subclasses of TextEntity share the same propreties !!
    static std::set<const Property*> properties;
};

#endif // TEXT_HPP
