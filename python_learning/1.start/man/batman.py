from bat import Bat
from superhero import Superhero


# 定义 Batman 作为子类，来同时继承 SuperHero 和 Bat
class Batman(Superhero, Bat):
    def __init__(self, *args, **kwargs):
        # 通常要继承属性，你必须调用 super:
        # super(Batman, self).__init__(*args, **kwargs)
        # 然而在这里我们处理的是多重继承，而 super() 只会返回 MRO 列表的下一个基础类。
        # 因此，我们需要显式调用初始类的 __init__
        # *args 和 **kwargs 传递参数时更加清晰整洁，而对于父类而言像是 “剥了一层洋葱”
        Superhero.__init__(
            self, "anonymous", *args, movie=True, superpowers=["Wealthy"], **kwargs
        )
        Bat.__init__(self, *args, can_fly=False, **kwargs)
        # 重写了 name 字段
        self.name = "Sad Affleck"

    def sing(self):
        return "nan nan nan nan nan batman!"


if __name__ == "__main__":
    sup = Batman()

    # 获取方法解析顺序 MRO，MRO 被用于 getattr() 和 super()
    # 这个字段是动态的，并且可以被修改
    print(Batman.__mro__)  # => (<class '__main__.Batman'>,
    # => <class 'superhero.Superhero'>,
    # => <class 'human.Human'>,
    # => <class 'bat.Bat'>, <class 'object'>)

    # 根据 C3 线性化算法的具体步骤：
    # 开始于 Batman，添加 Batman 到 MRO。
    # 按顺序处理 Batman 的父类，首先是 Superhero，然后是 Bat。
    # Superhero 继承 Human，所以先处理 Superhero，再处理 Human。
    # 处理完 Superhero 和 Human 后，再处理 Bat。
    # 最后添加 object。

    # 调用父类的方法并且使用子类的属性
    print(sup.get_species())  # => Superhuman

    # 调用被重写的类
    print(sup.sing())  # => nan nan nan nan nan batman!

    # 调用 Human 上的方法，(之所以是 Human 而不是 Bat)，是因为继承顺序起了作用
    sup.say("I agree")  # => Sad Affleck: I agree

    # 调用仅存在于第二个继承的父类的方法
    print(sup.sonar())  # => ))) ... (((

    # 继承类的属性
    sup.age = 100
    print(sup.age)  # => 100

    # 从第二个类上继承字段，并且其默认值被重写
    print("Can I fly? " + str(sup.fly))  # => Can I fly? False
