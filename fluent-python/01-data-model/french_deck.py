import collections
from random import choice

Card = collections.namedtuple("Card", ["rank", "suit"])


class FrenchDeck:
    _ranks: list[str] = [str(n) for n in range(2, 11)] + list("JQKA")
    _suits: list[str] = ["spades", "diamonds", "clubs", "hearts"]

    def __init__(self) -> None:
        self.cards = [Card(rank, suit) for rank in self._ranks for suit in self._suits]

    def __len__(self):
        return len(self.cards)

    def __getitem__(self, key):
        return self.cards[key]

    def __iter__(self):
        return iter(self.cards)


def spades_high(card: Card) -> int:
    suit_values = dict(spades=3, hearts=2, diamonds=1, clubs=0)
    rank_values: dict[str, int] = {
        rank: i for i, rank in enumerate(FrenchDeck._ranks, start=2)
    }
    rank_values.update(dict(J=11, Q=12, K=13, A=14))
    return rank_values[card.rank] * len(suit_values) + suit_values[card.suit]


if __name__ == "__main__":
    deck = FrenchDeck()
    print(deck.cards[:3])
    print(deck.cards[-3:])

    print(f"Number of cards: {len(deck)}")
    first_card = deck[0]
    print(f"First card: {first_card}")
    print(f"First card rank: {first_card.rank}")

    print(f"Random card: {choice(deck)}")

    first_N = deck[:5]
    for i, card in enumerate(first_N):
        print(f"{i + 1}: {card}")

    print("All cards:")
    for card in sorted(deck, key=spades_high):
        print(card)
