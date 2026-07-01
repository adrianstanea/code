from pydantic import BaseModel, PositiveFloat


class DiscountStrategy(BaseModel):
    def calculate(self, total: PositiveFloat) -> PositiveFloat:
        raise NotImplementedError("Subclasses must implement this method")


class NoDiscount(DiscountStrategy):
    def calculate(self, total: PositiveFloat) -> PositiveFloat:  # noqa: ARG002
        return 0.0


class PercentageDiscount(DiscountStrategy):
    percentage: PositiveFloat

    def calculate(self, total: PositiveFloat) -> PositiveFloat:
        return total * (self.percentage / 100)


class FixedAmountDiscount(DiscountStrategy):
    amount: PositiveFloat

    def calculate(self, total: PositiveFloat) -> PositiveFloat:
        return min(self.amount, total)


class CompositeDiscount(DiscountStrategy):
    discounts: list[DiscountStrategy] = []

    def calculate(self, total: PositiveFloat) -> PositiveFloat:
        return sum(discount.calculate(total) for discount in self.discounts)


class DiscountBuilder:
    def __init__(self) -> None:
        self._discounts: list[DiscountStrategy] = []

    def add_percentage_discount(self, percentage: PositiveFloat) -> "DiscountBuilder":
        if any(isinstance(discount, PercentageDiscount) for discount in self._discounts):
            raise ValueError("Only one percentage discount can be added")

        self._discounts.append(PercentageDiscount(percentage=percentage))
        return self

    def add_fixed_amount_discount(self, amount: PositiveFloat) -> "DiscountBuilder":
        self._discounts.append(FixedAmountDiscount(amount=amount))
        return self

    def build(self) -> DiscountStrategy:
        composite = CompositeDiscount()
        composite.discounts = self._discounts
        return composite


class ShoppingCart(BaseModel):
    discount: DiscountStrategy = NoDiscount()
    items: list[PositiveFloat] = []

    def add_item(self, price: PositiveFloat) -> None:
        self.items.append(price)

    def subtotal(self) -> PositiveFloat:
        return sum(self.items)

    def checkout(self) -> PositiveFloat:
        total = self.subtotal()
        discount_value = self.discount.calculate(total)
        return total - discount_value


if __name__ == "__main__":
    cart = ShoppingCart()
    cart.add_item(100)
    cart.add_item(50)

    print(f"Total without discount: {cart.checkout()}")

    cart.discount = PercentageDiscount(percentage=10)
    print(f"Total with 10% discount: {cart.checkout()}")

    cart.discount = FixedAmountDiscount(amount=30)
    print(f"Total with $30 discount: {cart.checkout()}")

    discount_builder = DiscountBuilder()
    discount_builder.add_percentage_discount(percentage=10)
    discount_builder.add_fixed_amount_discount(amount=20)
    cart.discount = discount_builder.build()
    print(f"Total with combined discounts: {cart.checkout()}")
