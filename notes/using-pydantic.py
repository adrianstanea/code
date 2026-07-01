from uuid import uuid1

from pydantic import UUID1, BaseModel


class User(BaseModel):
    id: UUID1
    name: str


if __name__ == "__main__":
    user = User(id=uuid1(), name="Alice")

    print(user)
    print(user.model_dump())
    print(user.model_dump_json())
