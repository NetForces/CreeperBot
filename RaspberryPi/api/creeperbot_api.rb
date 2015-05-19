require "sinatra"
require "net/http"
require "rubygems"

RobotIP="10.0.9.44"

get "/LightOn" do
	Net::HTTP.get(URI("http://#{RobotIP}/?LightOn"))
end

get "/LightOff" do
	Net::HTTP.get(URI("http://#{RobotIP}/?LightOff"))
end

get "/EyesOn" do
	Net::HTTP.get(URI("http://#{RobotIP}/?EyesOn"))
end

get "/EyesOff" do
	Net::HTTP.get(URI("http://#{RobotIP}/?EyesOff"))
end

get "/LightStrobe" do
	Net::HTTP.get(URI("http://#{RobotIP}/?LightStrobe"))
end

get "/Front" do
	Net::HTTP.get(URI("http://#{RobotIP}/?Front"))
end

get "/Right" do
	Net::HTTP.get(URI("http://#{RobotIP}/?Right"))
end

get "/Left" do
	Net::HTTP.get(URI("http://#{RobotIP}/?Left"))
end

get "/Back" do
	Net::HTTP.get(URI("http://#{RobotIP}/?Back"))
end

get "/Stop" do
	Net::HTTP.get(URI("http://#{RobotIP}/?Stop"))
end
