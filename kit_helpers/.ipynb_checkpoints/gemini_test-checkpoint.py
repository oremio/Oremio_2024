import google.generativeai as genai
from google.colab import userdata

GOOGLE_API_KEY = userdata.get("GOOGLE_API_KEY")
genai.configure(api_key=GOOGLE_API_KEY)

model = genai.GenerativeModel("gemini-1.0-pro")
response = model.generate_content("Please give me python code to sort a list.")
print(response.text)
