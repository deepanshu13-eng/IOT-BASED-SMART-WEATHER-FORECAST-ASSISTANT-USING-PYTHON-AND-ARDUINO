import urllib.request                                                      #Importing url library to open thingspeak url and to fedge data.
import pyttsx3                                                             #Importing pyttsx3 library to make our assistant to speak.
import re                                                                  #Importing regex library to cut some lines from the data and to convert it into usefull information.
                                           
engine = pyttsx3.init('sapi5')                                             #Setting up voice type, speech rate and other necessary things related to speech.
voices = engine.getProperty('voices')
rate = engine.getProperty('rate')
engine.setProperty('rate', rate-10)
engine.setProperty('voice',voices[0].id)

def speak(audio):                                                          #Defining a speak function to make our work easy in upcoming lines of code.
	engine.say(audio)
	engine.runAndWait()



data = urllib.request.urlopen("https://api.thingspeak.com/channels/1106704/feeds.json?api_key=TV1X4G5FBOVV1HSM&results=1")   # Requesting for url to get open. 
data =repr(data.read())                                                                                                      # Making the data coming from the url to read.



description = data[67:]                                                                                                      #Fetching description from the raw data. 
writeDescription = description[:63]

field1 = data[390:]                                                        #Fetching temperature value from the raw data.
temperature = field1[:2]

field2 = data[404:]                                                        #Fetching humidity value from the raw data
humidity = field2[:2]


date = data[276:]                                                          #Fetching updated date from the raw data.
updatedate = date[:10]

field3 = data[418:]                                                        #Fetching rain value from the raw data. 
rain = field3[:1]


speak("hello sir my name is automation. I will tell you the weather forecast of today. I use to collect data from my personal thingspeak server and let you know todays weather report" + writeDescription + "sir you can ask me your query related to weather forecast") #Introduction line
if __name__=="__main__":

	while True:
		temp = str()                           #Assigning temp as a string value.
		water = str()                          #Assigning water as a string value.
		if int(rain) == 0:
			water = "its not raining"          #Using if/else condition to print something if the condition is satisfied.  
		else:
			water = "its raining"
		if int(temperature) < 20:
			
			temp = "cool"
		elif int(temperature) >= 20 and int(temperature) <= 25:
		
			temp = "warm"
		elif int(temperature) >= 26:
			temp = "very hot"
		
		   
		
		query1 = str()                        #Assigning query as a string value.
		query1 = input("Please enter your query: ")  #Taking a input query.
		
		if 'tell me weather forecast of today' in query1:          #If the queary is this then it will do all this steps.
			speak("sir according to the latest entry that I can see on the thingspeak server is on" + updatedate + "the temperature on this day is" +temperature + "the humidity value on this day is" + humidity + water)
			print("Last updated date :" + updatedate)
			print("Temperature Value :" + temperature)
			print("Humidity Value:" + humidity)
			print("Rain Value" + rain)

		elif 'tell me temperature value' in query1:                #If the queary is this then it will do all this steps.
			speak("sir according to the latest entry that I can see is on" + updatedate + "the temperature value on this day is" + temperature + "degree celcius. The temperature is" + temp + "on this day")
			print("Last updated date : " + updatedate)
			print("Temperature Value : " + temperature)
		elif 'tell me humidity value' in query1:                   #If the queary is this then it will do all this steps.
			speak("sir according to the latest entry that I can see is on" + updatedate + "the humidity value on this day is " + humidity + "percent")
			print("Last updated date :" + updatedate)
			print("Humidity Value : " + humidity)
		elif 'tell me rain conditions' in query1:                  #If the queary is this then it will do all this steps.
			speak("sir according to the latest entry that I can see on the thingspeak server is on" + updatedate + water)   #Assistant will speak this.
			print("Last updated date :" + updatedate)
			print("Rain Value : " + rain)



