import tensorflow as tf
import pandas

config = tf.ConfigProto(device_count = {'GPU': 0, 'CPU': 1}, log_device_placement = True)
session = tf.Session(config = config)
tf.keras.backend.set_session(session)
tf.debugging.set_log_device_placement(True)

data = pandas.read_csv("diabetes.csv", header=None)
trainX, trainY = data.iloc[:,:-1], data.iloc[:,-1]

model = tf.keras.Sequential([
    tf.keras.layers.Flatten(input_shape=([8])),
    tf.keras.layers.Dense(8, activation=tf.nn.relu),
    tf.keras.layers.Dense(2, activation=tf.nn.softmax)
])
model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])
model.fit(trainX, trainY, epochs=10000)