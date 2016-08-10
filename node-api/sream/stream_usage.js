/**
 * A stream is an abstract interface implemented by various objects in Node.
 * 
 * For example a request to an HTTP server is a stream, as is stdout. Streams are readable, writable, or both. All streams are instances of EventEmitter.
 *
 * You can load the Stream base classes by doing require('stream').
 * 
 * There are base classes provided for Readable streams, Writable streams, Duplex streams, and Transform streams.
 *
 * This document is split up into 3 sections.
 * The first explains the parts of the API that you need to be aware of to use streams in your programs. If you never implement a streaming API yourself, you can stop there.
 * The second section explains the parts of the API that you need to use if you implement your own custom streams yourself. The API is designed to make this easy for you to do.
 * The third section goes into more depth about how streams work, including some of the internal mechanisms and functions that you should probably not modify unless you definitely know what you are doing.
 */

 /**
 *	API for Stream Consumers
 *
 * Class: stream.Readable
 * Event: 'readable'		流中有数据可读，此时可调用read()函数循环读取数据。
 * Event: 'data'			监听此事件会转入流动模式 数据尽可能快的交付事件处理函数
 * Event: 'end'				流中的数据全部被读出 监听'data'事件 进入流动模式自动消费全部流 或者 重复调用read()函数消费掉全部流 可触发此事件
 * Event: 'close'			在底层 资源 被关闭时 触发， 并不是所有流都能触发此事件
 * Event: 'error'			在读取流过程中出现错误
 *
 * readable.read([size])	用在非流动模式下，'readable'事件触发时，获取流中的数据。流动模式下此函数被自动调用知道buffer drained。没有数据可读是返回null
 * 		size Number Optional argument to specify how much data to read
 *		Return String | Buffer | null
 *
 * readable.setEncoding(encoding)	调用此函数会使流 返回 指定编码的字符串代替buffer对象。不要自己读出buffer之后在调用buf.toString(encoding)转换成目标编码的字符串
 * 		encoding String The encoding to use.
 *
 * readable.resume()	继续发射'data'事件 转入流动模式 可以在不想消费数据的情况下 获取'end'事件。
 *
 * readable.pause() 	可以停止在流动模式下的流发射'data'事件 数据将被保持在内部的buffer中 只在流动模式下有效 在非流动模式下调用会使流转入流动模式暂停
 *
 * readable.pipe(destination, [options])	自动管理流
 * 		destination Writable Stream The destination for writing data
 *		options Object Pipe options end Boolean End the writer when the reader ends. Default = true 控制流在全部被消费后触发'end'事件时，可写流是否关闭。
 *
 * readable.unpipe([destination])	停止pipe
 *
 * readable.unshift(chunk)	用于跳过一些不希望的数据，过滤
 *
 * readable.wrap(stream)	包裹旧版本的流
 *
 *
 * Class: stream.Writable
 * writable.write(chunk, [encoding], [callback])	写数据到底层系统 数据被缓存会返回false
 * 		chunk String | Buffer The data to write
 * 		encoding String The encoding, if chunk is a String
 * 		callback Function Callback for when this chunk of data is flushed
 * 		Returns: Boolean True if the data was handled completely.
 *
 * Event: 'drain'	当向底层系统写入数据时，如果数据被缓存，则此事件将表明适合继续向底层写入数据
 *
 * writable.end([chunk], [encoding], [callback])	向底层表明没有更多的数据可写，回调函数和'finish'事件处理函数一致。end()之后不能继续写数据。
 * 		chunk String | Buffer Optional data to write
 * 		encoding String The encoding, if chunk is a String
 * 		callback Function Optional callback for when the stream is finished
 *
 * Event: 'finish' 	当end()函数调用后，所有缓存的数据被刷新到底层系统，此事件会递交。
 * Event: 'pipe'		pipe()
 * Event: 'unpipe'	unpipe()
 * Event: 'error'		write()或pipe()时出错。
 */