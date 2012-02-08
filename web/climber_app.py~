import web
import scl
import json
import mpylayer

urls = (
    '/', 'index',
    '/play', 'play',
    '/lift', 'lift',
    '/start_jog', 'startJog',
    '/stop_jog', 'stopJog',
)

render = web.template.render('templates/')

db = web.database(dbn='sqlite',db='climbing')

#s = scl.SCL('/dev/ttyUSB0')

app = web.application(urls, globals())

db_var_tbl = 'video_data'

#mp = mpylayer.MPlayerControl()

def get_db_variable(var):
    t = db.select(db_var_tbl)
    for i in t:
        if i['variable'] == var:
            return i['value']
    return None

def set_db_variable(var,val):
    db.update(db_var_tbl,where="variable=$var",value=val,vars = locals())

class index:
    
    def GET(self):
        return render.index()

class startJog:

    def GET(self):
        pass
#       return s.startJog()

class stopJog:
    
    def GET(self):
        pass
 #       return s.stopJog()

class lift:

	def POST(self):
		print "received movement data"
		input = web.input()
		buttonName = input['func']
		amount = input['amt']
		return self.processButton(buttonName, amount)
		
	def processButton(self,buttonName,amount):
		if(buttonName.indexOf('up') != -1):
			return self.moveProjector(float(amount))		
		if(buttonName.indexOf('down') != -1):
			return self.moveProjector(0 - float(amount))		
		
	def moveProjector(self,amount):
		print "moving projector " + str(amount)
		current_height = get_db_variable('height')
		current_height += float(amount)
		set_db_variable('height', current_height)
		return json.dumps({'height':current_height})

class play:

    def POST(self):
        input = web.input()
        buttonName = input['func']
        return self.processButton(buttonName)

    def processButton(self,buttonName):
        if(buttonName == 'play-button'):
            return self.playButtonPressed()
        if(buttonName == 'stop-button'):
            return self.stopButtonPressed()
        if(buttonName == 'rewind-button'):
            return self.rewindButtonPressed()
        if(buttonName == 'fast_forward-button'):
            return self.fastForwardButtonPressed()
        if(buttonName == 'beginning-button'):
            return self.beginningButtonPressed()
        if(buttonName == 'end-button'):
            return self.endButtonPressed()

    def playButtonPressed(self):
        video_play_status = get_db_variable('status')
        if video_play_status == 'stopped':
            mp.loadfile('climbing.mov')
            video_play_status = 'playing'
            set_db_variable('status',video_play_status)
            return json.dumps({'status':video_play_status})
        if video_play_status == 'playing':
            mp.pause()
            video_play_status = 'paused'
            set_db_variable('status',video_play_status)
            return json.dumps({'status':video_play_status})
        if video_play_status == 'paused':
            mp.pause()
            video_play_status = 'playing'
            set_db_variable('status',video_play_status)
            return json.dumps({'status':video_play_status})

    def stopButtonPressed(self):
        mp.stop()
        set_db_variable('status','stopped')
        return json.dumps({'status':'stopped'})

    def rewindButtonPressed(self):
        mp.time_pos -= 1
        return json.dumps({'time':mp.time_pos})

    def fastForwardButtonPressed(self):
        mp.time_pos += 1
        return json.dumps({'time':mp.time_pos})

    def beginningButtonPressed(self):
        mp.time_pos = 0.0
        return json.dumps({'time':mp.time_pos})

    def endButtonPressed(self):
        return json.dumps({'time':mp.time_pos})

class lift:

    def POST(self):
        pass

if __name__=="__main__":
    app.run()
