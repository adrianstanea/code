#include <print>

class MilesEstimator {
   public:
    virtual ~MilesEstimator() = default;

    int getMilesLeft() const {
        return this->getGallonsLeft() * this->getMilesPerGallon();
    }

    void setGallonsLeft(int gallons) { m_gallonsLeft = gallons; }
    int getGallonsLeft() const { return m_gallonsLeft; }

   private:
    [[nodiscard]] virtual int getMilesPerGallon() const {
        return m_millesPerGallon;
    }

   private:
    int m_gallonsLeft{0};
    static constexpr int m_millesPerGallon{20};
};

class EfficientCarMilesEstimator : public MilesEstimator {
   private:
    [[nodiscard]] int getMilesPerGallon() const override {
        return m_millesPerGallon;
    }

   private:
    static constexpr int m_millesPerGallon{30};
};

int main(int argc, const char** argv) {
    auto miles_estimator{MilesEstimator()};
    miles_estimator.setGallonsLeft(3);
    std::println("Miles Estimator: {}", miles_estimator.getMilesLeft());

    auto efficient_miles_estimator{EfficientCarMilesEstimator()};
    efficient_miles_estimator.setGallonsLeft(3);
    std::println("Efficient Miles Estimator: {}",
                 efficient_miles_estimator.getMilesLeft());

    return 0;
}