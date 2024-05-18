####################################################
## 6. 类
####################################################

# 我们使用 "class" 语句来创建类
class Human:
    # 一个类的字段。 这个字段共享给这个类的所有实例。
    species = "H. sapiens"

    # 构造方法，当实例被初始化时被调用。注意名字前后的双下划线，这是表明这个属性
    # 或方法对 Python 有特殊意义，但是允许用户自行定义。
    # 方法(可能是对象或者属性) 类似: __init__, __str__,__repr__ etc
    # 都是特殊的方法
    # 你自己取名时不应该用这种格式
    def __init__(self, name):
        # 将参数赋值给实例的 name 字段
        self.name = name

        # 初始化属性
        self._age = 0

    # 实例方法，第一个参数总是self，也就是这个实例对象
    def say(self, msg):
        print("{name}: {message}".format(name=self.name, message=msg))

    # 另一个实例方法
    def sing(self):
        return "yo... yo... microphone check... one two... one two..."

    # 类方法，被所有此类的实例共用。
    # 第一个参数是这个类对象。
    @classmethod
    def get_species(cls):
        return cls.species

    # 静态方法。调用时没有实例或类的绑定。
    @staticmethod
    def grunt():
        return "*grunt*"

    # property 有点类似 getter
    # 它把方法 age() 转换为同名并且只读的属性
    # 通常情况下，可以不需要编写复杂的 getter 和 setter。
    @property
    def age(self):
        return self._age

    # 允许属性被修改
    @age.setter
    def age(self, age):
        self._age = age

    # 允许属性被删除
    @age.deleter
    def age(self):
        del self._age


# 当 Python 解释器在读取源文件的时候，就会执行文件中所有的代码
# 对 __name__ 的检查可以保证这块代码只会在这个模块是主程序的情况下被运行（而不是在引用时运行）
if __name__ == "__main__":
    i = Human(name="Ian")
    i.say("hi")  # "Ian: hi"
    j = Human("Joel")
    j.say("hello")  # "Joel: hello"
    # i 和 j 都是 Human 实例化后的对象，换一句话说，它们都是 Human 实例

    # 运行类方法 (classmethod)
    i.say(i.get_species())  # "Ian: H. sapiens"
    # 修改共享的类属性
    Human.species = "H. neanderthalensis"
    i.say(i.get_species())  # => "Ian: H. neanderthalensis"
    j.say(j.get_species())  # => "Joel: H. neanderthalensis"

    # 运行静态方法 (staticmethod)
    print(Human.grunt())  # => "*grunt*"

    # 实例上也可以执行静态方法
    print(i.grunt())  # => "*grunt*"

    # 更新实例的属性
    i.age = 42
    # 访问实例的属性
    i.say(i.age)  # => "Ian: 42"
    j.say(j.age)  # => "Joel: 0"
    # 删除实例的属性
    del i.age
    # i.age                         # => 这会抛出一个错误: AttributeError
