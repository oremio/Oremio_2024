####################################################
## 6.1 类的继承
####################################################

# 继承机制允许子类可以继承父类上的方法和变量。
# 我们可以把 Human 类作为一个基础类或者说叫做父类，
# 然后定义一个名为 Superhero 的子类来继承父类上的比如 "species"、 "name"、 "age" 的属性
# 和比如 "sing" 、"grunt" 这样的方法，同时，也可以定义它自己独有的属性

# 基于 Python 文件模块化的特点，你可以把这个类放在独立的文件中，比如说，human.py。

# 要从别的文件导入函数，需要使用以下的语句
# from "filename-without-extension" import "function-or-class"

from human import Human

# 指定父类作为类初始化的参数
class Superhero(Human):

    # 如果子类需要继承所有父类的定义，并且不需要做任何的修改，
    # 你可以直接使用 "pass" 关键字（并且不需要其他任何语句）
    # 但是在这个例子中会被注释掉，以用来生成不一样的子类。

    # pass

    # 子类可以重写父类定义的字段
    species = 'Superhuman'

    # 子类会自动的继承父类的构造函数包括它的参数，但同时，子类也可以新增额外的参数或者定义，
    # 甚至去覆盖父类的方法比如说构造函数。
    # 这个构造函数从父类 "Human" 上继承了 "name" 参数，同时又新增了 "superpower" 和
    # "movie" 参数:
    def __init__(self, name, movie=False,
                 superpowers=["super strength", "bulletproofing"]):

        # 新增额外类的参数
        self.fictional = True
        self.movie = movie
        # 注意可变的默认值，因为默认值是共享的
        self.superpowers = superpowers

        # "super" 函数让你可以访问父类中被子类重写的方法
        # 在这个例子中，被重写的是 __init__ 方法
        # 这个语句是用来运行父类的构造函数:
        super().__init__(name)

    # 重写父类中的 sing 方法
    def sing(self):
        return 'Dun, dun, DUN!'

    # 新增一个额外的方法
    def boast(self):
        for power in self.superpowers:
            print("I wield the power of {pow}!".format(pow=power))


if __name__ == '__main__':
    sup = Superhero(name="Tick")

    # 检查实例类型
    if isinstance(sup, Human):
        print('I am human')
    if type(sup) is Superhero:
        print('I am a superhero')

    # 获取方法解析顺序 MRO，MRO 被用于 getattr() 和 super()
    # 这个字段是动态的，并且可以被修改
    print(Superhero.__mro__)    # => (<class '__main__.Superhero'>,
                                # => <class 'human.Human'>, <class 'object'>)

    # 调用父类的方法并且使用子类的属性
    print(sup.get_species())    # => Superhuman

    # 调用被重写的方法
    print(sup.sing())           # => Dun, dun, DUN!

    # 调用 Human 的方法
    sup.say('Spoon')            # => Tick: Spoon

    # 调用 Superhero 独有的方法
    sup.boast()                 # => I wield the power of super strength!
                                # => I wield the power of bulletproofing!

    # 继承类的字段
    sup.age = 31
    print(sup.age)              # => 31

    # Superhero 独有的字段
    print('Am I Oscar eligible? ' + str(sup.movie))
