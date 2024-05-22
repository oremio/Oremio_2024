offer_list = ["Allen", "Tom"]
for i in offer_list:
    print(
        f"{i}, you have passed our interview and will soon become a member of our company."
    )
offer_list[1] = "Andy"
for i in offer_list:
    print(f"{i}, welcome to join us!")
